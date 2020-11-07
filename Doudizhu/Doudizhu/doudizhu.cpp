#include<stdlib.h>
#include<time.h>
#include<stdio.h>
#define NDEALS 3000
#define NPLAYERS 6
typedef enum { clubs, diamonds, hearts, spades } cdhs; //�����ƣ�ö������
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
	int pips;//�˿��Ƶ��� 
	cdhs suit;//�˿��ƻ�ɫ 
	card decks[52];//�ṹ������ 52���� ÿ���ƶ������ֺͻ�ɫ��� 
	for (int i = 0;i<52;i++)//�������˿��ƽ��и�ֵ���� 
	{  /*pade�����ң�bai�������ȣ���heart�����ģ��������ң���club��÷���������ݻ�����
	   diamond������dao������ש��*/
		pips = i % 13 + 1;
		if (i<13)
			suit = clubs;//13��÷�� 
		else if (i<26)
			suit = diamonds;
		else if (i<39)
			suit = hearts;
		else
			suit = spades;
		decks[i] = assign_values(pips, suit);//pips�����ϵ����� suit�ǻ�ɫ 
	}
	for (int i = 26;i<39;i++)
	{
		prn_card_values(&decks[i]);
	}
	play_poker(decks);
	return 0;
}
//��ĳ���˿��ƽ��и�ֵ 
card assign_values(int pips, cdhs suit)
{
	card c;
	c.pips = pips;
	c.suit = suit;
	return c;
}
//��ӡ��ĳ���˿��ƵĻ�ɫ�͵���
void  prn_card_values(card *c_ptr)//�����ô���
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
//����
void play_poker(card deck[52])
{
	int flush_cnt = 0, hand_cnt = 0;
	int i, j;
	card hand[NPLAYERS][5];//ÿ����������
	srand(time(NULL)); /*һ����rand������һ������������ĺ�����
					   ��srand��һ��������������ӵĺ�����ͨ������������
					   ��һ��ʹ�õģ�����ɲ���������Ĺ��ܣ�*/
	for (i = 0;i<NDEALS;i++)
	{
		shuffle(deck);//ÿһ�ζ�ϴ�� 
		deal_the_cards(deck, hand);
		for (j = 0;j<NPLAYERS;j++)
			++hand_cnt;
		if (is_flush(hand[j]))
		{
			++flush_cnt;//����ͬ����
			printf("%s%d\n%s%d\n%s%f\n\n",
				"   Hand  number: ", hand_cnt,
				"   Flush number: ", flush_cnt,
				"Flush probability: ", (double)flush_cnt / hand_cnt);
		}
	}

}
//ϴ��
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