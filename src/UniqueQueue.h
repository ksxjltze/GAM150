#pragma once
#include <queue>
#include <set>
#include <vector>

template <typename T>
class unique_queue
{
private:
    std::queue<T> m_queue;
    std::set<T> m_set;
public:

    inline size_t size() const
    {
        return m_queue.size();
    }

    inline bool empty() const
    {
        return m_queue.empty();
    }

    void push(const T& t)
    {
        if (m_set.insert(t).second) 
        {
            m_queue.push(t);
            //printf("unique (pushed into Q)\n");
        }
        //printf("Not unique (not pushed into Q)\n");
    }
   
    void pop()
    {   
        if (!m_queue.empty())
        {
            const T& val = front();

            typename std::set<T>::iterator it = m_set.find(val);
            if (it != m_set.end())
            {
                m_set.erase(it);
                m_queue.pop();
            }  
        }
        else
            printf("Queue is empty\n");
       
    }
  

    const T& front() const
    {
        return m_queue.front();
    }
};