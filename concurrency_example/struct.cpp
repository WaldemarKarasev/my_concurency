#include <utility>

struct bucket
{
    int a;
    int b;
};


bucket fill(int a, int b)
{
    bucket bckt;
    bckt.a = a;
    bckt.b = b;
    return bckt;
}

int main()
{

    bucket b = fill(1, 2);

    b.a += 1;

}