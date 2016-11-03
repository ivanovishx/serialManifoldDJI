// =============================================================================
//
//  net.hpp
//  Airspace Application
//
//  Created by Guy Bar-Nahum on 7/19/16.
//  Copyright © 2016 Defense Labs. All rights reserved.
//
// =============================================================================

#ifndef __THREAD_HPP__
#define __THREAD_HPP__

#include <pthread.h>


// .................................................................... thread_c
//

class thread_c
{
private:

    static void * thread_entry_stub(void * t)
    {
    
        ((thread_c *)t)->thread_entry();
     
        return NULL;
    }

    pthread_t _thread;

protected:

    // subclass this method with the code you want your thread to run
    virtual void thread_entry() = 0;

public:
    // ................................................ constructor + destructor
    thread_c() {}
    virtual ~thread_c() {}

    // .................................................................. create
    // Returns
    //         true if the thread was successfully started,
    //         false if there was an error starting the thread
    bool create()
    {
        return (pthread_create(&_thread, NULL, thread_entry_stub, this) == 0);
    }

    // ............................................................... wait_join
    // will not return until the internal thread has exited.
    void wait_join()
    {
        (void) pthread_join(_thread, NULL);
    }
    
};

#endif // __THREAD_HPP__

