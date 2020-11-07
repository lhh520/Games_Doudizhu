#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#define NDEALS 3000
#define NPLAYERS 6
typedef enum { clubs, diamonds, hearts, spades } cdhs; //四种牌：枚举类型
struct  card
{
	int pips;
	cdhs suit;
};
card assign_values(int pips, cdhs suit);
void  prn_card_values(card *c_ptr);
void shuffle(card deck[52]);
void play_poker(card deck[52]);
void deal_the_cards(card decks[52], card hand[NPLAYERS][5]);
int is_flush(card h[5]);
void swap(card *p, card *q);
using namespace std;
int main()
{
	int pips;//扑克牌点数 
	cdhs suit;//扑克牌花色 
	card decks[52];//结构体数组 52张牌 每个牌都有数字和花色组成 
	for (int i = 0;i<52;i++)//对整幅扑克牌进行赋值操作 
	{  /*pade（黑桃，bai又名葵扇）、heart（红心，又名红桃）、club（梅花，又名草花）、
	   diamond（方块dao又名阶砖）*/
		pips = i % 13 + 1;
		if (i<13)
			suit = clubs;//13张梅花 
		else if (i<26)
			suit = diamonds;
		else if (i<39)
			suit = hearts;
		else
			suit = spades;
		decks[i] = assign_values(pips, suit);//pips是牌上的数字 suit是花色 
	}
	for (int i = 26;i<39;i++)
	{
		prn_card_values(&decks[i]);
	}
	play_poker(decks);
	return 0;
}
//对某个扑克牌进行赋值 
card assign_values(int pips, cdhs suit)
{
	card c;
	c.pips = pips;
	c.suit = suit;
	return c;
}
//打印出某个扑克牌的花色和点数
void  prn_card_values(card *c_ptr)//按引用传递
{
	int pips = c_ptr->pips;
	int suit = c_ptr->suit;
	char *suit_name;
	if (suit == clubs)
		suit_name = "clubs";
	if (suit == diamonds)
		suit_name = "diamonds";
	if (suit == hearts)
		suit_name = "hearts";
	if (suit == spades)
		suit_name = "spades";
	printf("card: %2d of %s\n", pips, suit_name);
}
//发牌
void play_poker(card deck[52])
{
	int flush_cnt = 0, hand_cnt = 0;
	int i, j;
	card hand[NPLAYERS][5];//每个人五张牌
	srand(time(NULL)); /*一个是rand（）是一个产生随机数的函数！
					   而srand是一个设置随机数种子的函数！通常这两个函数
					   是一起使用的！来完成产生随机数的功能！*/
	for (i = 0;i<NDEALS;i++)
	{
		shuffle(deck);//每一次都洗牌 
		deal_the_cards(deck, hand);
		for (j = 0;j<NPLAYERS;j++)
			++hand_cnt;
		if (is_flush(hand[j]))
		{
			++flush_cnt;//计数同花数
			printf("%s%d\n%s%d\n%s%f\n\n",
				"   Hand  number: ", hand_cnt,
				"   Flush number: ", flush_cnt,
				"Flush probability: ", (double)flush_cnt / hand_cnt);
		}
	}

}
//洗牌
void shuffle(card deck[52])
{
	int i, j;
	for (i = 0;i<52;i++)
	{
		j = rand() % 52;
		swap(&deck[i], &deck[j]);
	}
}
void swap(card *p, card *q)
{
	card tmp;
	tmp = *p;
	*p = *q;
	*q = tmp;
}
//
void deal_the_cards(card decks[52], card hand[NPLAYERS][5])
{
	int card_cnt = 0, i, j;
	for (j = 0;j<5;j++)
		for (i = 0;i<NPLAYERS;i++)
		{
			hand[i][j] = decks[card_cnt++];
		}
}
int is_flush(card h[5])
{
	int i;
	for (i = 1;i<5;i++)

		if (h[i].suit != h[0].suit)
			return 0;
	return 1;
}