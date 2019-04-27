#include<iostream>
#include <queue>
using namespace std;

const int max_search = 15;//最大搜索步骤数


class mf_state
{
public:
	mf_state* parents = nullptr;
	int last_change = 0;//这个点是上一个的last_change+1个子节点
	int depth = 0;
	char surface1[6];
	char surface2[6];
	char surface3[6];
	char surface4[6];
	int n_children = 0;
	mf_state* children[4];
	mf_state();
	mf_state(char c1[6], char c2[6], char c3[6], char c4[6]);
	mf_state* changestate1();
	mf_state* changestate2();
	mf_state* changestate3();
	mf_state* changestate4();
};
mf_state::mf_state(char c1[6], char c2[6], char c3[6], char c4[6])
{
	for (int i = 0;i < 6;i++)
	{
		this->surface1[i] = c1[i];
		this->surface2[i] = c2[i];
		this->surface3[i] = c3[i];
		this->surface4[i] = c4[i];
	}

}

mf_state::mf_state()
{}
mf_state* mf_state::changestate1()
{
	mf_state* p = new mf_state;
	for (int i = 0;i < 6;i++)//旋转1时 面1不变
	{
		p->surface1[i] = this->surface1[i];
		if (i == 3 or i == 4 or i == 5)
		{
			p->surface2[i] = this->surface2[i];
			p->surface3[i] = this->surface3[i];
			p->surface4[i] = this->surface4[i];
		}
		else
		{
			p->surface4[i] = this->surface2[i];
			p->surface2[i] = this->surface3[i];
			p->surface3[i] = this->surface4[i];
		}
	}
	return p;
}

mf_state* mf_state::changestate2()
{
	mf_state* p = new mf_state;
	for (int i = 0;i < 6;i++)
	{
		p->surface2[i] = this->surface2[i];
		if (i == 3 or i == 4 or i == 5)
		{
			p->surface1[i] = this->surface1[i];
		}
		if (i == 1 or i == 2 or i == 3)
		{
			p->surface3[i] = this->surface3[i];
		}
		if (i == 0 or i == 1 or i == 5)
		{
			p->surface4[i] = this->surface4[i];
		}
		//下面是发生变化的
		p->surface1[2] = this->surface4[2];
		p->surface1[1] = this->surface4[3];
		p->surface1[0] = this->surface4[4];

		p->surface3[0] = this->surface1[0];
		p->surface3[5] = this->surface1[1];
		p->surface3[4] = this->surface1[2];

		p->surface4[2] = this->surface3[4];
		p->surface4[3] = this->surface3[5];
		p->surface4[4] = this->surface3[0];
	}
	return p;
}

mf_state* mf_state::changestate3()
{
	mf_state* p = new mf_state;
	for (int i = 0;i < 6;i++)
	{
		p->surface3[i] = this->surface3[i];
		if (i == 0 or i == 1 or i == 5)
		{
			p->surface1[i] = this->surface1[i];
			p->surface2[i] = this->surface2[i];
		}

		if (i == 1 or i == 2 or i == 3)
		{
			p->surface4[i] = this->surface4[i];
		}
		//下面是发生变化的
		p->surface2[4] = this->surface4[0];
		p->surface2[3] = this->surface4[5];
		p->surface2[2] = this->surface4[4];

		p->surface4[0] = this->surface1[2];
		p->surface4[5] = this->surface1[3];
		p->surface4[4] = this->surface1[4];

		p->surface1[2] = this->surface2[4];
		p->surface1[3] = this->surface2[3];
		p->surface1[4] = this->surface2[2];
	}
	return p;
}

mf_state* mf_state::changestate4()
{
	mf_state* p = new mf_state;
	for (int i = 0;i < 6;i++)
	{
		p->surface4[i] = this->surface4[i];
		if (i == 1 or i == 2 or i == 3)
		{
			p->surface1[i] = this->surface1[i];
			p->surface2[i] = this->surface2[i];
		}

		if (i == 0 or i == 1 or i == 5)
		{
			p->surface3[i] = this->surface3[i];
		}
		//下面是发生变化的
		p->surface2[4] = this->surface1[0];
		p->surface2[5] = this->surface1[5];
		p->surface2[0] = this->surface1[4];

		p->surface3[2] = this->surface2[4];
		p->surface3[3] = this->surface2[5];
		p->surface3[4] = this->surface2[0];

		p->surface1[0] = this->surface3[2];
		p->surface1[5] = this->surface3[3];
		p->surface1[4] = this->surface3[4];
	}
	return p;
}

void print_state(mf_state* test)
{
	cout << endl << "底面：" << endl;
	for (int i = 0;i < 6;i++)
	{
		if (i == 3)
		{
			cout << endl;
		}
		if (i < 3)
		{
			cout << test->surface1[i];
		}
		else
		{
			cout << test->surface1[8 - i];
		}
	}
	cout << endl << "正面：" << endl;
	for (int i = 0;i < 6;i++)
	{
		if (i == 3)
		{
			cout << endl;
		}
		if (i < 3)
		{
			cout << test->surface2[i];
		}
		else
		{
			cout << test->surface2[8 - i];
		}
	}
	cout << endl << "左面：" << endl;
	for (int i = 0;i < 6;i++)
	{
		if (i == 3)
		{
			cout << endl;
		}
		if (i < 3)
		{
			cout << test->surface3[i];
		}
		else
		{
			cout << test->surface3[8 - i];
		}
	}
	cout << endl << "右面：" << endl;
	for (int i = 0;i < 6;i++)
	{
		if (i == 3)
		{
			cout << endl;
		}
		if (i < 3)
		{
			cout << test->surface4[i];
		}
		else
		{
			cout << test->surface4[8 - i];
		}
	}
}
bool check_complete(mf_state test)
{
	for (int i = 1;i < 6;i++)
	{
		if (test.surface1[i] != test.surface1[0])
			return 0;
		if (test.surface2[i] != test.surface2[0])
			return 0;
		if (test.surface3[i] != test.surface3[0])
			return 0;
		if (test.surface4[i] != test.surface4[0])
			return 0;
	}

	return 1;
}
void grow_the_tree_once(mf_state* root)
{

	root->children[0] = root->changestate1();
	root->children[1] = root->changestate2();
	root->children[2] = root->changestate3();
	root->children[3] = root->changestate4();

	for (int i = 0;i < 4;i++)
	{
		root->children[i]->depth = root->depth + 1;
		root->children[i]->parents = root;
		root->children[i]->last_change = i + 1;
	}
	root->n_children = 4;
	cout << root->depth << endl;
}


mf_state*  build_the_tree(mf_state* root)
{
	queue<mf_state *> nodeQueue;  //使用C++的STL标准模板库
	nodeQueue.push(root);
	mf_state * node;
	while (!nodeQueue.empty()) {
		node = nodeQueue.front();//node就是当前遍历的节点
		if (check_complete(*node))
		{
			return node;
		}
		if (node->depth > max_search)
		{
			cout << "超过搜索限制，请检查输入" << endl;
			return nullptr;
		}

		grow_the_tree_once(node);
		nodeQueue.pop();

		for (int i = 0;i < 4;i++)
		{
			nodeQueue.push(node->children[i]);
		}

	}

	return nullptr;
}
void release_the_tree(mf_state* p)
{
	if (p->n_children != 0)
	{
		for (int i = p->n_children - 1; i >= 0; i--)
		{
			release_the_tree(p->children[i]);
		}
	}
	if (p->parents != nullptr)
	{
		p->parents->n_children--;
		delete p;
	}

}

void print_ans(mf_state* p)
{
	if (p->parents != nullptr)
	{
		cout << p->last_change;
		print_ans(p->parents);
	}
}
int main()
{
	char c1[6] = { 'y','y','y','y','y','y' };
	char c2[6] = { 'g','g','g','g','g','g' };
	char c3[6] = { 'b','b','b','b','b','b' };
	char c4[6] = { 'r','r','r','r','r','r' };
	char c[7];

	cout << "输入底面面颜色" << endl;
	cin >> c;
	for (int i = 0;i < 6;i++)
	{
		c1[i] = c[i];
	}
	cout << "输入正面颜色" << endl;
	cin >> c;
	for (int i = 0;i < 6;i++)
	{
		c2[i] = c[i];
	}
	cout << "输入左面颜色" << endl;
	cin >> c;
	for (int i = 0;i < 6;i++)
	{
		c3[i] = c[i];
	}
	cout << "输入右面颜色" << endl;
	cin >> c;
	for (int i = 0;i < 6;i++)
	{
		c4[i] = c[i];
	}

	mf_state* root = new mf_state(c1, c2, c3, c4);
	mf_state* ans = build_the_tree(root);
	cout << "四面体魔方开始求最优解：" << endl;
	print_ans(ans);

	release_the_tree(root);
	delete root;
	system("pause");
	return 0;
}