#include "stream.h"

Stream::Stream(int x)
{
    int length = getRandomLength();

    headX = x;
    headY = 0;

    for (int i = 0; i < length; i++)
    {
        charList.push_back(getRandomChar());
    }
}

int Stream::getRandomLength()
{
    return rand() % (MAX_LENGTH - MIN_LENGTH) + MIN_LENGTH;
}

char Stream::getRandomChar()
{
    return rand() % ('Z' - 'A' + 1) + 'A';
}

void Stream::move()
{
    charList.push_front(getRandomChar());
    charList.pop_back();
    headY += 1;
}

void Stream::display()
{
    int charIndex = 0;

    for (auto charIter = charList.begin(); charIter != charList.end(); ++charIter, ++charIndex)
    {
        int x = headX;
        int y = headY - charIndex;

        attron(COLOR_PAIR((charIndex == 0) ? WHITE : GREEN));
        mvaddch(y, x, *charIter);
    }
}

int Stream::getHeadX()
{
    return headX;
}

int Stream::getHeadY()
{
    return headY;
}

int Stream::getLength()
{
    return charList.size();
}
