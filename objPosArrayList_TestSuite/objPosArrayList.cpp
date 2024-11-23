#include "objPosArrayList.h"

// Check lecture contents on general purpose array list construction, 
// and modify it to support objPos array list construction.

objPosArrayList::objPosArrayList()
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[ARRAY_MAX_CAP];
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        //the snake cannot extend any farther because it's at its max size
        return;
    }

    // shift the elements back by one slot to make room for the inclusion of the head
    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; 
    }

    aList[0] = thisPos;
    listSize++; 

}

void objPosArrayList::insertTail(objPos thisPos)
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    //no need to shuffle elements because we are appending the tail to the end of the list where there are assumingly empty spaces.
    aList[listSize] = thisPos;
    listSize++; 
}

void objPosArrayList::removeHead()
{   
    //we can't remove an element of the snake if it doesn't exist.
    if (listSize == 0){
        return;
    }

    //shift all the elements one position towards the tail so the head can be easily removed
    for(int i = 0; i<listSize-1; i++){
        aList[i] = aList[i+1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    if (listSize == 0){
        return;
    }
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize-1];
}

objPos objPosArrayList::getElement(int index) const
{
    //error troubleshooting to ensure the index chosen is not out of bounds of our list
    if (index < 0 || index >= listSize)
    {
        return objPos();
    }

    return aList[index];
}