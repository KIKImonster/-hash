RT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<vector>
using namespace std;
//实现一个闭散列

enum Statu
{
	EMPTY,
	EXIST,
	DELETE//删除状态用于表示非空状态，但下个数据可以写入，
};
template<class K, class V>
struct HashNode
{
	pair<K, V> _kv = pair<K, V>();
	Statu _state = EMPTY;
};
template<class K, class V>

class HashTable
{
public:
	typedef HashNode<K, V> Node;
	HashTable(size_t n = 5)
		:_size(0)
	{
		_ht.resize(n);
	}
	bool insert(const pair<K, V>&  kv)
	{
		checkCapcity();
		int idx = kv.first % _ht.size();//通过函数计算位置
		//判断当前位置是否可插入  空可插入，空 或者 删除状态可插入
		while (_ht[idx]._state = EXIST)//
		{
			if (_ht[idx]._state == EXIST && _ht[idx]._kv.first == kv.first)
				return false;
			++idx;
			//判断是否越界
			if (idx == _ht.size())
				idx = 0;
		}
		//为空直接插入
		_ht[idx]._kv = kv;
		_ht[idx]._state = EXIST;
		++_size;
		return true;
		
	}
	void checkCapcity()
	{
		//负载因子：元素个数/空间大小  负载因子：决定哈希冲突发生的大小，和空间利用率
		//引入负载因子的概念作为平衡空间和时间的效率
		//线性探测中，负载因子一定小于1，靠近1，冲突概率变大
		if (_size * 10 / _ht.size() >= 7)//0.7负载因子,便于计算的情况下扩大十倍，将size*10
		{
			//扩容
			int newC = _ht.size() == 0 ? 5 : 2 * _ht.size();
			//重新插入：空间改变之后，数据位置可能发生改变

			HashTable<K, V> newHT(newC);
			//把旧表元素插入新表
			for (int i = 0; i < _ht.size(); ++i)
			{
				if (_ht[i]._state == EXIST)
					newHT.insert(_ht[i]._kv);
			}
			swap(_ht, newHT._ht);
			//free newHT;
		}
	}
	Node* find(const K& key)
	{
		int idx = key % _ht.size();
		while (_ht[idx]._state != EMPTY)
		{
			/*while (_ht[idx]._kv != key)
			{
				idx++;
			}
			return _ht[idx];*/
			if (_ht[idx]._state == EXIST && _ht[idx]._kv.first == key)
				return &_ht[idx];
			idx++;
			if (idx == _ht.size())
				idx = 0;
		}
		return nullptr;
	}
	bool erase(const K& key)
	{
		if (Node* de = find(key))
		{
			de->_state = DELETE;
			--_size;
			cout << "delete true" << endl;
			return true;
		}
		return false;
	}
private:
	vector<Node> _ht;
	size_t _size;//表示实际元素个数
};

void test()
{
	HashTable<int, int> ht;
	ht.insert(make_pair(5, 5));
	ht.insert(make_pair(15, 15));
	ht.insert(make_pair(10, 10));
	ht.insert(make_pair(7, 7));
	ht.insert(make_pair(8, 8));
	ht.insert(make_pair(9, 9));
	ht.insert(make_pair(2, 2));

	ht.find(15);
	ht.erase(15);
	
	
}

int main()
{
	test();
	return 0;
}

