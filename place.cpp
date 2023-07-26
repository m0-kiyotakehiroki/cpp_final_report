#include<iostream>
#include<fstream>
#include<random>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

int rou(int n) {   //サイコロ?の作製（動作確認済み）　die(n)で1からnが出るルーレット。n=6でサイコロ。
	int die1 = 0;
	random_device engine;
	uniform_int_distribution<unsigned> dist1(1, n);
	die1 = dist1(engine);

	return die1;
}

string Map[61] = { "[スタート]","□","□" ,"□" ,"□" ,"◇" ,"□" ,"□" ,"□" ,"□" ,"◇" ,
							   "□" ,"□" ,"□" ,"□" ,"◇" ,"□" ,"□" ,"□" ,"□" ,"◇" ,
							   "□" ,"□" ,"□" ,"□" ,"☆" ,"□" ,"□" ,"□" ,"□" ,"◇" ,
							   "□" ,"□" ,"□" ,"□" ,"◇" ,"□" ,"□" ,"□" ,"□" ,"◇" ,
							   "□" ,"□" ,"□" ,"□" ,"◇" ,"□" ,"□" ,"□" ,"□" ,"◇" ,
							   "□" ,"□" ,"□" ,"□" ,"◇" ,"□" ,"□" ,"□" ,"□" ,"[最終試練]" };     //マップのマスの形設定

class Quiz {
	string quiz;
	string choice;
	int  ans = 0;
	string  explain;
public:
	void setQuiz(const string& newQuiz) { quiz = newQuiz; }
	string getQuiz() { return quiz; }
	void setChoice(const string& newChoice) { choice = newChoice; }
	string getchoiice() { return choice; }
	void setAns(int newAns) { ans = newAns; }
	int getAns() { return ans; }
	void setExplain(const string& newExplain) { explain = newExplain; }
	string getExplain() { return explain; }
};

vector<Quiz> vec;//クイズを保管する箱

vector<int> quizNumbe;//出題前のクイズを保管する箱

void setquizNumber() {
	for (int n = 0; n < 70; n++)
	{
		quizNumbe.push_back(n);
	}
}

void setquiz() {
	ifstream datafile("quiz.dat");
	string quiz;
	string choice;
	int x;
	string exp;

	int i = 0;
	while (datafile >> quiz >> choice >> x >> exp) {
		vec.emplace_back();
		vec[i].setQuiz(quiz);
		vec[i].setChoice(choice);
		vec[i].setAns(x);
		vec[i].setExplain(exp);
		++i;
	}
	datafile.close();
}

void PrintMap(int n2) {    //双六マップの作製(動作確認済み)　n2が現在のスタートからの距離（０はスタート、３０でゴールマス）
	for (int i2 = 0; i2 <= 60; i2++) {
		if (i2 == n2) {
			if (n2 == 25) {
				cout << "★";
			}
			else if (n2 % 5 == 0) {
				cout << "◆";
			}
			else {
				cout << "■";
			}
		}
		else {
			cout << Map[i2];
		}
	}
}

int EVENT(int mapn) {
	int a1 = 0;
	int a2 = 0;
	int a3 = 0;
	if (mapn == 25) {
		PrintMap(mapn);
		cout << endl;

		a3 = rou(5);
		a1 = mapn - a3;//乱数により問題を決定

		auto end = remove(quizNumbe.begin(), quizNumbe.end(), a1);
		quizNumbe.erase(end, quizNumbe.cend()); //２行で最終試練に同じ問題が出ないように、vectorから問題番号を削除

		int a = 0;
		cout << vec[a1].getQuiz() << endl;
		cout << vec[a1].getchoiice() << endl;
		cin >> a;
		if (a == vec[a1].getAns())
		{
			cout << "〇" << endl;
			a2 = 7;
		}
		else
		{
			cout << "×" << "正解は" << vec[a1].getAns() << endl;
			a2 = -1;
		}
		cout << vec[a1].getExplain() << endl;
		cout << endl;

	}
	else if (mapn % 5 == 0) {
		PrintMap(mapn);
		cout << endl;
		a3 = rou(5);
		a1 = mapn - a3;//乱数により問題を決定

		auto end = remove(quizNumbe.begin(), quizNumbe.end(), a1);
		quizNumbe.erase(end, quizNumbe.cend()); //２行で最終試練に同じ問題が出ないように、vectorから問題番号を削除

		int a = 0;
		cout << vec[a1].getQuiz() << endl;
		cout << vec[a1].getchoiice() << endl;
		cin >> a;
		if (a == vec[a1].getAns())
		{
			cout << "〇" << endl;
			a2 = rou(2) + 1;
		}
		else
		{
			cout << "×" << "正解は" << vec[a1].getAns() << endl;
			a2 = -1;
		}
		cout << vec[a1].getExplain() << endl;
		cout << endl;

	}

	return a2;
}

int FinalEVENT(int number) {
	int a3 = 0;
	int a4 = 0;
	int a5 = 0;
	int a6 = 0;

	random_device get_rand_dev;
	mt19937 get_rand_mt(get_rand_dev());
	shuffle(quizNumbe.begin(), quizNumbe.end(), get_rand_mt);

	while (a4 < 5) {
		a5 = quizNumbe[0];
		quizNumbe.erase(quizNumbe.begin());

		int a7 = 0;
		cout << vec[a5].getQuiz() << endl;
		cout << vec[a5].getchoiice() << endl;

		cin >> a7;
		if (a7 == vec[a5].getAns())
		{
			cout << "〇" << endl;
			a3 += 1;
		}
		else
		{
			cout << "×" << "正解は" << vec[a5].getAns() << endl;
			a4 += 5;
		}
		cout << vec[a5].getExplain() << endl;
		cout << endl;
		a4 += 1;
	}

	if (a3 >= 5) {
		a6 = 3;
	}
	else {
		a6 = a3 - 5;
		if (a6 == -5) {
			a6 = -4;
		}
	}

	return a6;
}

int main() {
	int a = 0;	  //クイズの結果を入れるよう
	int p = 0;    //現在位置
	int rp = 0;   //残りマス
	int lp = 0;  //最終得点計算用
	int die2;    //サイコロの出目を入れる箱
	int p0 = 0;//説明確認の選択用
	int p1 = 0;//残りターン数の管理
	int p2 = 0;//行動選択の入力
	int p3 = 0;//ゲーム終了時のポイント用
	int p4 = 0;//最終得点計算用
	int p5 = 0;//最終試練の結果判定用

	setquiz();  //クイズの設定
	setquizNumber(); //クイズ管理箱の作成

	cout << "タイムスリップ！日本史すごろくへようこそ！\n半角数字のみを入力し、入力が完了したらエンターキーを押してください。\n説明を見ますか？\n1.YES(見る)　　　　2.NO(見ない)" << endl;  //welcomeコメント
	cin >> p0;
	if (p0 == 1) {//ルール説明
		cout << "＜説明＞\n1.行動はサイコロを振るか１マス進むかから選べます。\n2.◇や☆マスにとまると、クイズが出題され、正解すると2～3マス進め、不正解だと1ターン余計に消費します。。" << endl;
		cout << "3.最後のマス、最終試練では5問問題が出され、連続5問正解するとゴールとなります。\n4.最終試練では、問題に間違えると、正解数に応じて後ろに戻されます。" << endl;
		cout << "5.全部で60マスあります。\n6.最終試練以外の問題に1問正解するごとに100ポイント、ゴールした時の残りターン数の10倍のポイントが入り、その合計がゲームの得点となります。最終試練ではポイントが入りません。\n7.25ターン以内にゴール出来ないとゲームオーバーです。" << endl;
	}

	cout << "それではゲームを始めます。" << endl;

	PrintMap(-1);
	cout << endl;

	while (p < 61) {
		cout << "\n残り" << 25 - p1 << "ターンです" << endl;
		cout << "使うサイコロの数をうち、エンターキーを押してください" << endl;
		cout << "1.サイコロをひとつ振る  2.１マス進む";
		cout << endl;


		cin >> p2;
		if (p2 == 2) {
			p += 1;
			cout << "１マス進みました" << endl;
		}
		else {
			die2 = rou(6);
			p += die2;
			cout << "サイコロの出た目は" << die2 << "です" << endl;
		}

		if (p > 59) {
			p = 60;
			p5 = FinalEVENT(60);
			p += p5;
		}

		a = EVENT(p);
		if (a > 1) {
			p += a;
			p3 += 100;
		}
		else if (a < 0) {
			p += 1;
			rp += 1;
			p3 += 10;
		}


		if (p < 61) {
			rp = 60 - p;
		}
		else {
			lp = rp;
			rp = 0;
		}

		p1 += 1;

		cout << "残り" << rp << "マスです" << endl;
		PrintMap(p);
		cout << endl;
		if (p1 >= 25) {
			p = 65;
		}
	}
	if (p1 == 25) {
		cout << "ゲームオーバー\nまたトライしてね";
	}
	else {
		p4 = lp * 10;
		p3 += p4;
		cout << "ゴール" << endl;
		cout << "得点は" << p3 << "点です" << endl;
		cout << "Thank you for playing" << endl;

	}

}