#include "list.h"
#include "stock.h"


void func1 (good_t good) {
    printf("Stock received %s of volume %i\n", good_getName(good), good_getVolume(good));
}

void func2 (good_t good) {
    printf("%s of volume %i was delievered on stock\n", good_getName(good), good_getVolume(good));
}

int main()
{
    stock_t stock = stock_new("B07-Y", 100);
    good_t goods[5];
    goods[0] = good_new("Sugar", 5);
    goods[1] = good_new("Rume", 15);
    goods[2] = good_new("Wood", 50);
    goods[3] = good_new("Fure", 30);
    goods[4] = good_new("Salt", 7);
    user_t user1 = user_new("User1");
    user_t user2 = user_new("User2");
    Callback cb1 = &func1;
    Callback cb2 = &func2;
    stock_subscride(stock, user1, cb1);
    stock_subscride(stock, user2, cb2);
    for (int i = 0; i < 5; i++)
        stock_add(stock, goods[i]);






    user_free(user1);
    user_free(user2);
    for(int i = 0; i < 5; i++) {
        good_free(goods[i]);
    }
    stock_free(stock);
    return 0;
}
