#include <iostream>
#include <iomanip>

using namespace std;

//���� ������
struct TreeNode
{
	int data;
	short bal;
	TreeNode *left, *right;
};

//������� ����
struct QueueNode
{
	TreeNode *trans;
	QueueNode *next;
};


class Queue
{
private:
	QueueNode *Head;
public:
	Queue() { Head = NULL; }
	int isEmpty();
	void addToQueue(TreeNode *tmp);
	TreeNode *delQueue()
	{
		QueueNode *cur = Head->next;
		TreeNode *tmp_c = Head->trans;

		if (Head != NULL)
		{
			delete Head;
			Head = cur;
			return tmp_c;
		}
		else
			return NULL;
	}
};


int Queue::isEmpty()
{
	if (Head == NULL)
		return 1;
	else
		return 0;
}


void Queue::addToQueue(TreeNode *tmp)
{
	QueueNode *Ptr = new QueueNode;
	Ptr->trans = tmp;

	if (Head == NULL)
	{
		Head = Ptr;
		Ptr->next = NULL;
	}
	else
	{
		QueueNode *tmp_c = Head;

		while (tmp_c->next != NULL)
			tmp_c = tmp_c->next;

		tmp_c->next = Ptr;
		Ptr->next = NULL;
	}
}



class Tree
{
private:
	TreeNode *root, *next;
public:
	Tree() { root = NULL; } //�����������
	Tree(int TreeNode); //����������� � ����������
	Tree(const Tree&); //����������� �����
	~Tree() { //����������
		delete[] root;
	}

	//����� � ������
	void levelOrder()                  
	{
		Queue Universal;
		Universal.addToQueue(root);

		TreeNode *tmp;

		while (!Universal.isEmpty())
		{
			tmp = Universal.delQueue();
			cout << tmp->data << " ";

			if (tmp->left != NULL)
				Universal.addToQueue(tmp->left);
			if (tmp->right != NULL)
				Universal.addToQueue(tmp->right);
		}
	}

	void addToTreeHelper(int value)
	{
		addToTree(&root, value);
	}

	//���������� ��������
	void addToTree(TreeNode **Ptr, int value)
	{
		if ((*Ptr) == NULL)
		{
			(*Ptr) = new TreeNode;
			(*Ptr)->data = value;
			(*Ptr)->left = (*Ptr)->right = NULL;
		}
		else
		{
			if (value < (*Ptr)->data)
				addToTree(&(*Ptr)->left, value);
			else if (value >(*Ptr)->data)
				addToTree(&(*Ptr)->right, value);
			else
				cout << "��������!" << endl;
		}
		balanceHelper();
	}

	void deleteTreeHelp(int value)
	{
		deleteTree(root, value);
	}

	//�������� ��������
	void deleteTree(TreeNode *Ptr, int value)
	{
		TreeNode *parent = NULL;
		TreeNode *removed = NULL;

		while (Ptr != NULL && Ptr->data != value)
		{
			parent = Ptr;
			if (Ptr->data > value)
				Ptr = Ptr->left;
			else
				Ptr = Ptr->right;
		}

		int peremen = Ptr->data;

		if (root != NULL)
		{
			TreeNode *child = NULL;
			if (Ptr->left == NULL || Ptr->right == NULL)
			{
				/*������ ����� ���� �������*/
				if (Ptr->left == NULL)
					child = Ptr->right;
				else
					child = Ptr->left;

				/*���� ������� ������ � ����� ��������*/
				if (root->data == value)
					root = child;
				else
				{
					if (parent->left == Ptr)
						parent->left = child;
					else
						parent->right = child;
				}

				removed = Ptr;
			}
			else            /*if(Ptr -> left != NULL || Ptr -> right != NULL)*/
			{
				/*������ ����� 2 �������*/
				TreeNode *mostLeft = Ptr->right;

				while (mostLeft->left != NULL)
				{
					parent = mostLeft;
					mostLeft = mostLeft->left;
				}

				if (root->data == value) {
					removed = mostLeft;

					if (parent->left == mostLeft)
						parent->left = NULL;
					else
						parent->right = NULL;

					root->data = mostLeft->data;
				}
				else
				{
					removed = mostLeft;

					if (Ptr->left == mostLeft)
						Ptr->left = NULL;
					else
						Ptr->right = NULL;

					Ptr->data = mostLeft->data;
				}
			}
		}

		delete removed;
	}

	void outputHelper(int totalSpace)
	{
		outputTree(root, totalSpace);
	}

	//����� ������
	void outputTree(TreeNode *Ptr, int totalSpace)
	{
		while (Ptr != NULL)
		{
			outputTree(Ptr->right, totalSpace + 5);

			for (int i = 1; i <= totalSpace; i++)
				cout << " ";

			cout << Ptr->data << "\n";

			Ptr = Ptr->left;
			totalSpace += 5;
		}
	}

	void outputHelperPlus(int totalSpace)
	{
		outputTreePlus(root, totalSpace);
	}

	//������ ������������� ���������
	void outputTreePlus(TreeNode *Ptr, int totalSpace)
	{
		while (Ptr != NULL)
		{
			for (int i = 1; i <= totalSpace; i++)
				cout << " ";
			if ((Ptr->data)<0) {
				(Ptr->data) = (Ptr->data)*(-1);
			}

			Ptr = Ptr->left;
			totalSpace += 5;
		}
	}

	void MinValueHelper() {
		MinValue(root);
	}

	//����������� ������� ������ 
	void MinValue(TreeNode *Ptr) {
		while (Ptr->left != NULL ) {
			Ptr = Ptr->left;
		}
		cout << ( Ptr->data);
	}

	
	// ���������� ������� �������
	short factor(TreeNode *Ptr) {
		short fr = (Ptr->right != NULL) ? Ptr->right->bal : 0;
		short fl = (Ptr->left != NULL) ? Ptr->left->bal : 0;
		return (fr - fl);
	}

	void balanceHelper() {
		balance(root);
	}

	// ������������ ����
	TreeNode* balance(TreeNode *Ptr) {

		short lh = (Ptr->left != NULL) ? Ptr->left->bal : 0;
		short rh = (Ptr->right != NULL) ? Ptr->right->bal : 0;
		Ptr->bal = ((lh > rh) ? lh : rh) + 1;
		short fac = factor(Ptr);
		if (fac == 2) {
			if (factor(Ptr->right) < 0)
				Ptr->right = rotate(Ptr->right, false);
			return rotate(Ptr, true);
		}
		else if (fac == -2) {
			if (factor(Ptr->left) > 0)
				Ptr->left = rotate(Ptr->left, true);
			return rotate(Ptr, false);
		}
		return Ptr;
	}

	// ������� ����� ��� ������
	TreeNode* rotate(TreeNode *Ptr, bool left) {
		short lh, rh;
		TreeNode* t;
		if (left) {
			t = Ptr->right;
			Ptr->right = t->left;
			t->left = Ptr;
		}
		else {
			t = Ptr->left;
			Ptr->left = t->right;
			t->right = Ptr;
		}

		lh = (Ptr->left != NULL) ? Ptr->left->bal : 0;
		rh = (Ptr->right != NULL) ? Ptr->right->bal : 0;
		Ptr->bal = ((lh > rh) ? lh : rh) + 1;

		lh = (t->left != NULL) ? t->left->bal : 0;
		rh = (t->right != NULL) ? t->right->bal : 0;
		t->bal = ((lh > rh) ? lh : rh) + 1;
		return t;
	}

};


void menu()
{
	cout << "1 - �������� �������." << endl;
	cout << "2 - ����� ������" << endl;
	cout << "3 - ������� �������" << endl;
	cout << "4 - �������� ������������� �������� ��������������" << endl;
	cout << "5 - ����� ����������� ������� ������" << endl;
	cout << "6 - �����." << endl;
}


int main()
{
	setlocale(LC_ALL, "Russian");

	Tree Universal;
	int c, value, space = 0;

	do {
		menu();
		cout << endl;
		cin >> c;

		switch (c)
		{
		case 1:
			cout << "������� �����: ";
			cin >> value;
			Universal.addToTreeHelper(value);
			Universal.levelOrder();
			break;
		case 2:
			cout << "����� ������:\n\n";
			Universal.outputHelper(space);
			Universal.levelOrder();
			break;
		case 3:
			cout << "������� �������� ���������� ��������: ";
			cin >> value;
			Universal.deleteTreeHelp(value);
			Universal.levelOrder();
			break;
		case 4:
			cout << "������ ������������� ��������� ������ �����������." << endl;
			Universal.outputHelperPlus(space);
			Universal.levelOrder();
			cout << endl;
			break;
		case 5:
			cout << "���������� ������� ������: ";
			Universal.MinValueHelper();
			cout << endl;
			break;
		case 6:
			exit(0);
		default: cout << "�������� ����� ����!" << endl;
		}
		system("Pause");
		system("cls");
	} while (c != 6);

	return 0;
}