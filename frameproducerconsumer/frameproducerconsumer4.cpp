#include <vector>
#include <thread>
#include <memory>
#include <queue>
#include <mutex>

#ifdef HAVE_OPENCV

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#else


#endif
using namespace std;

template <class T>
class ThreadSafeQueue
{
	std::queue<T> m_queue;
	std::mutex m_mutex;
        public:
	void push(const T &ba){
		std::lock_guard<std::mutex> lg(m_mutex);
		m_queue.push(ba);
	};
	
	T top () {
               	std::lock_guard<std::mutex> lg(m_mutex);
		return m_queue.front();
	}

	void pop() {
 		std::lock_guard<std::mutex> lg(m_mutex);
                if (!m_queue.empty())
                	m_queue.pop();
	}

       	T top_pop() { // atomic action to get the top and also immediatelt pop it,
                      // so another consumer will not cut in between my top and pop action
                std::lock_guard<std::mutex> lg(m_mutex);
                T tmp = NULL;
                if (!m_queue.empty()) {
                        tmp = m_queue.front();
                        m_queue.pop();
                }
                return tmp;
        }

        bool empty() {
               std::lock_guard<std::mutex> lg(m_mutex);
               return m_queue.empty();
	}

        int size() {
              std::lock_guard<std::mutex> lg(m_mutex);
              return m_queue.size();
 
	}
};


struct ThreadSafeContainer
{ 
    ThreadSafeQueue<unsigned char*> displayConsumer;
    ThreadSafeQueue<unsigned char*> fileSaveConsumer;
    ThreadSafeQueue<unsigned char*> imageProcessingConsumer;

};

char byteArray[10000];
#define MAXLOOP 1000
struct Producer
{

    public:

    Producer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }
 
    void stop()
    {
	StopRequested = true;
    }

    void run()
    {
        StopRequested = false;

        while(true)
        {
            if ( (container->displayConsumer.size() >= MAXLOOP) ||
                 (container->fileSaveConsumer.size() >= MAXLOOP) ||
                 (container->imageProcessingConsumer.size() >= MAXLOOP)) {
                std::this_thread::yield();
                //printf(" ");
                continue;
	    }

            // grab image from camera
            // store image in container
#ifdef HAVE_OPENCV
            Mat image(400, 400, CV_8UC3, Scalar(10, 100,180) );
            unsigned char *pt_src = image.data;

#else
	    unsigned char *pt_src = (unsigned char *)&byteArray[0];//malloc(10000);
	    printf("+");//dummy action for now
#endif

            //copy frame to each consumer queue
            container->displayConsumer.push(pt_src);
            container->fileSaveConsumer.push(pt_src);
            container->imageProcessingConsumer.push(pt_src);

            std::this_thread::yield();
	    if (StopRequested)
		break;
	}
    }

    std::shared_ptr<ThreadSafeContainer> container;
    bool StopRequested;
};

struct DisplayConsumer
{

    public:

    DisplayConsumer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }
    ~DisplayConsumer()
    {

    }

    void stop()
    {
        StopRequested = true;
    }

    void run()
    {   
        StopRequested = false;

        while(true)
        {
       
	        // if we are ahead of producer, wait a cycle
        	if (container->displayConsumer.empty())
		{
			std::this_thread::yield();
			continue;
		};

        	// read next image from container

        	if (!container->displayConsumer.empty())
            	{
                	unsigned char *ptr_consumer_Image;
                	ptr_consumer_Image = container->displayConsumer.top_pop(); //get the front of the queue which contain the pointer to the image data, also atomically remove it from queue

#ifdef HAVE_OPENCV
                	Mat image(400, 400, CV_8UC3);
                	image.data = ptr_consumer_Image;

                	imshow("consumer image", image);
#else
			printf("_"); // dummy fucntion for now
#endif
            	}    
            	std::this_thread::yield();   
            	if (StopRequested)
                	break;

        }
    }

    std::shared_ptr<ThreadSafeContainer> container;
    bool StopRequested;

};

struct FileSaveConsumer
{

    public:

    FileSaveConsumer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }
    ~FileSaveConsumer()
    {

    }

    void stop()
    {
        StopRequested = true;
    }

    void run()
    {

        StopRequested = false;

        while(true)
        {

       		// if we are ahead of producer, wait a cycle
        	if (container->fileSaveConsumer.empty())
        	{
                	std::this_thread::yield();
                	continue;
        	};


            	// read next image from container
        	if (!container->fileSaveConsumer.empty())
            	{
                	unsigned char *ptr_consumer_Image;
                	ptr_consumer_Image = container->fileSaveConsumer.top_pop(); //Get the front of the queue which contain the pointer to the image data, also atomically remove it from the queue

#ifdef HAVE_OPENCV
                	Mat image(400, 400, CV_8UC3);
                	image.data = ptr_consumer_Image;

                	imshow("consumer image", image);
#else
                	printf("="); // dummy fucntion for now
#endif
            	}
            	std::this_thread::yield();
            	if (StopRequested)
                	break;

        }
    }
    std::shared_ptr<ThreadSafeContainer> container;
    bool StopRequested;

};


struct ImageProcessingConsumer
{

    public:

    ImageProcessingConsumer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }
    ~ImageProcessingConsumer()
    {

    }

    void stop()
    {
        StopRequested = true;
    }

    void run()
    {

        StopRequested = false;

        while(true)
        {

                // if we are ahead of producer, wait a cycle
                if (container->imageProcessingConsumer.empty())
                {
                        std::this_thread::yield();
                        continue;
                };


                // read next image from container
                if (!container->imageProcessingConsumer.empty())
                {
                        unsigned char *ptr_consumer_Image;
                        ptr_consumer_Image = container->imageProcessingConsumer.top_pop(); //Get the front of the queue which contain the pointer to the image data, also atomically remove it from the queue

#ifdef HAVE_OPENCV
                        Mat image(400, 400, CV_8UC3);
                        image.data = ptr_consumer_Image;

                        imshow("consumer image", image);
#else
                        printf("i"); // dummy fucntion for now
#endif
                }
                std::this_thread::yield();
            	if (StopRequested)
                	break;

        }
    }

    std::shared_ptr<ThreadSafeContainer> container;
    bool StopRequested;

};



int main()
{
    //Pointer object to the class containing a "container" which will help "Producer" and "Consumer" to put and take images
    auto ptrObject_container = make_shared<ThreadSafeContainer>();

    //Pointer object to the Producer...intialize the "container" variable of "Struct Producer" with the above created common "container"
    auto ptrObject_producer = make_shared<Producer>(ptrObject_container);


    //FIRST Pointer object to the Consumer...intialize the "container" variable of "Struct Consumer" with the above created common "container"
    auto first_ptrObject_consumer = make_shared<DisplayConsumer>(ptrObject_container);

    //SECOND Pointer object to the Consumer...intialize the "container" variable of "Struct Consumer" with the above created common "container"
    auto second_ptrObject_consumer = make_shared<FileSaveConsumer>(ptrObject_container);


    //THIRD Pointer object to the Consumer...intialize the "container" variable of "Struct Consumer" with the above created common "container"
    auto third_ptrObject_consumer = make_shared<ImageProcessingConsumer>(ptrObject_container);

    //RUN producer thread
    thread producerThread(&Producer::run, ptrObject_producer);


    //RUN first thread of Consumer
    thread first_consumerThread(&DisplayConsumer::run, first_ptrObject_consumer);

    //RUN second thread of Consumer
    thread second_consumerThread(&FileSaveConsumer::run, second_ptrObject_consumer);

    //RUN third thread of Consumer
    thread third_consumerThread(&ImageProcessingConsumer::run, third_ptrObject_consumer);


    //JOIN all threads
    producerThread.join();
    first_consumerThread.join();
    second_consumerThread.join();
    third_consumerThread.join();

    return 0;
}
