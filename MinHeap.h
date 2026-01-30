/* Author: Grace Swartz (2414391, gswartz@chapman.edu) */
/* PA 6: Kruskal's */
/* Class: CPSC350-02 */
/* Date: 12/6/24 */
/* Summary: min heap implementation */

#ifndef MINHEAP_H
#define MINHEAP_H

template <typename T>
class MinHeap{
  public:
    MinHeap(int c);
    virtual ~MinHeap();
    void insert(T k);
    T getMin();
    void deleteMin();
    bool isEmpty(){ return m_size==0;}
  private:
    T* m_Heap; //how many things in heap
    int m_size;
    int m_cap; //what's max size of heap
    void fixHeap(int startIdx);
    int getLeftIdx(int i);
    int getRightIdx(int i);
    int getParentIdx(int i);
};

template <typename T>
MinHeap<T>::MinHeap(int c){
  m_Heap = new T[c];
  m_size = 0;
  m_cap = c;
}

template <typename T>
MinHeap<T>::~MinHeap(){
  delete[] m_Heap;
}

template <typename T>
T MinHeap<T>::getMin(){
  return m_Heap[0];
}

template <typename T>
int MinHeap<T>::getLeftIdx(int i){
  return (2*i)+1;
}

template <typename T>
int MinHeap<T>::getRightIdx(int i){
  return (2*i)+2;
}

template <typename T>
int MinHeap<T>::getParentIdx(int i){
  return (i-1)/2;
}

template <typename T>
void MinHeap<T>::insert(T k){
  m_Heap[m_size++] = k; // put it at last
  int currIdx = m_size - 1;
  // make sure thing is still a heap
  // swap with parent until valid
  while((currIdx > 0) && (m_Heap[currIdx] < m_Heap[getParentIdx(currIdx)])){
    T temp = m_Heap[currIdx];
    m_Heap[currIdx] = m_Heap[getParentIdx(currIdx)];
    m_Heap[getParentIdx(currIdx)] = temp;
    currIdx = getParentIdx(currIdx);

  }
}

template <typename T>
void MinHeap<T>::deleteMin(){
  if(m_size==1){
    --m_size;
    //return;
  }
  else{
    m_Heap[0] = m_Heap[m_size-1]; 
    --m_size;
    fixHeap(0); //fix heap starting at root
  }
}

template <typename T>
void MinHeap<T>::fixHeap(int startIdx){
  int left = getLeftIdx(startIdx); // get left index
  int right = getRightIdx(startIdx); // get right index
  int smallest = startIdx; // the smallest thing (aka what we want at root)
  // which of our children are the smallest? ok, smallest replaces parent
  if(left < m_size && m_Heap[left] < m_Heap[startIdx]){ // also checking that L and R didn't go off array
    smallest = left; 
  }
  if(right < m_size && m_Heap[right] < m_Heap[smallest]){
    smallest = right;
  }
  if(smallest != startIdx){//have to swap with child : if the smallest index (ex in class - 2) is not = to starting (in class - 0)
    // start where it needs swapped
    T temp = m_Heap[startIdx];
    m_Heap[startIdx] = m_Heap[smallest];
    m_Heap[smallest] = temp; 
    fixHeap(smallest);
  }
}

#endif