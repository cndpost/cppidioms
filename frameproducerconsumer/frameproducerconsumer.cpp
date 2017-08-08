#include <vector>
#include <thread>
#include <memory>
#include <queue>

#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

Mutex mu;

struct ThreadSafeContainer
{ 
    queue<unsigned char*> safeContainer;

};

struct Producer
{
    Producer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }

    void run()
    {
        while(true)
        {
            // grab image from camera
            // store image in container
            Mat image(400, 400, CV_8UC3, Scalar(10, 100,180) );
            unsigned char *pt_src = image.data;
            mu.lock();
            container->safeContainer.push(pt_src);
            mu.unlock();
        }
    }

    std::shared_ptr<ThreadSafeContainer> container;
};

struct Consumer
{
    Consumer(std::shared_ptr<ThreadSafeContainer> c) : container(c)
    {

    }
    ~Consumer()
    {

    }

    void run()
    {
        while(true)
        {
            // read next image from container
        mu.lock();
        if (!container->safeContainer.empty())
            {
                unsigned char *ptr_consumer_Image;
                ptr_consumer_Image = container->safeContainer.front(); //The front of the queue contain the pointer to the image data
                container->safeContainer.pop();

                Mat image(400, 400, CV_8UC3);
                image.data = ptr_consumer_Image;

                imshow("consumer image", image);
                waitKey(33);
            }       
            mu.unlock();
        }
    }

    std::shared_ptr<ThreadSafeContainer> container;
};



int main()
{
    //Pointer object to the class containing a "container" which will help "Producer" and "Consumer" to put and take images
    auto ptrObject_container = make_shared<ThreadSafeContainer>();

    //Pointer object to the Producer...intialize the "container" variable of "Struct Producer" with the above created common "container"
    auto ptrObject_producer = make_shared<Producer>(ptrObject_container);


    //FIRST Pointer object to the Consumer...intialize the "container" variable of "Struct Consumer" with the above created common "container"
    auto first_ptrObject_consumer = make_shared<Consumer>(ptrObject_container);

    //SECOND Pointer object to the Consumer...intialize the "container" variable of "Struct Consumer" with the above created common "container"
    auto second_ptrObject_consumer = make_shared<Consumer>(ptrObject_container);

    //RUN producer thread
    thread producerThread(&Producer::run, ptrObject_producer);


    //RUN first thread of Consumer
    thread first_consumerThread(&Consumer::run, first_ptrObject_consumer);

    //RUN second thread of Consumer
    thread second_consumerThread(&Consumer::run, second_ptrObject_consumer);

    //JOIN all threads
    producerThread.join();
    first_consumerThread.join();
    second_consumerThread.join();

    return 0;
}
