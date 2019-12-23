#include <iostream>

using namespace std;

/*
*Virtual Proxy
*/
struct Image 
{
    virtual void draw() = 0;
};

struct Bitmap : Image
{
    Bitmap(const string& filename): filename(filename)
    {
        cout << "Loading from " << filename << endl;
    }
    //
    void draw() override
    {
        cout << "Drawing image " << filename << endl;
    }
    const string filename;
};

/*
*the construct of LazyBitmap instance would not load the image data
*/
struct LazyBitmap : Image
{
    LazyBitmap(const string & filename) : filename(filename) {}
    ~LazyBitmap() {delete bmp;}
    void draw() override
    {
        if(!bmp)
            bmp = new Bitmap(filename);
        bmp->draw();
    }
    Bitmap *bmp{nullptr};
    const string filename;
};

void testVirtualProxy()
{
    Bitmap b{"test.jpg"};
    LazyBitmap lb{"test2.jpg"};
    b.draw();
    lb.draw();
}

/*
* Communication Proxy
*/

struct Pingable
{
    virtual wstring ping(const wstring& message) = 0;
};

struct Pong : Pingable
{
    wstring ping(const wstring& message) override
    {
        return message + L"pong";
    }
};

void tryit(Pingable& pp)
{
    wcout << pp.ping(L"ping") << "\n";
}


struct RemotePong : Pingable
{
    wstring piong(const wstring& message)
    {
        return L"Remote message";
    }
};

int main()
{
    testVirtualProxy();
    return 0;
}