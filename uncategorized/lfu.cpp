// http://blog.csdn.net/xnn2s/article/details/7310515
// http://ju.outofmemory.cn/entry/50447
// http://www.360doc.com/content/13/0805/16/13247663_304916783.shtml
今天也介绍一下 LFU 的实现方法。LRU 是最近最少使用算法，就是把最早才访问的数据淘汰掉。
LFU 是最近最不常用算法，就是某一段时间内被用到最少的淘汰掉。

LFU 时间周期
	使用次数的时间长度，这个时间不能太短，短了体现不出哪些数据是热点；
	同样也不能太长，太长的话，某一个时间点的对某个数据的访问峰值可以长期影响我们的淘汰策略。
	一般实现的算法可以根据业务特点去调节这个参数。

上个周期访问次数权重
	在本周期开始的时候，最粗暴的做法是把所有数据的访问数据全置成0。
	这样上次的访问热点就体现不出来了。
	考虑引入一个可调整的权重，这个权重一般建议与访问次数成反比的关系。

这个算法实现比LRU稍微简单一点。

数据访问次数数组
        数组内容是数据索引+访问次数，这个数组做成线性有序数组，按访问次数降序排列。
哈希表
        数据索引作为Key，指向数据访问时间数组的下标。

访问cache
        查哈希表，查到，返回数据。根据哈希表的值（就是上面的数组下标），定位到数组元素，
        将数组元素访问次加1，然后和后面元素做调整。
        没查到，数据不在cache中。如果cache未满，把该数据索引加到访问次数数组的尾部。
        满了，就要淘汰了，直接把访问次数数组的最后一个元素对应的数据淘汰掉；把新数据加到哈希表，
        同时将访问次数元素加到数组尾部。
对整个cache启动一个以LFU时间周期长度的定时器，定时时间到，就整个cache访问数组的访问次数按权重降低。
另外，如果某个数据的访问次数达到最大值了，所有的访问次数也按权重降低。
权重降低是一个对整个访问次数数组的遍历过程，但一般这个周期时间不会太短(至少分钟级)，
而且降权重过程时间很短(100W个数据约10ms)，整个过程不会产生CPU和内存访问的峰值。

#include <iostream>
#include <string>
#include <map>
#include <list>


struct CacheEntry{
public:
	int key;
	int value;
	// list freqNode;
	CacheEntry(int k, int v) :key(k), value(v) {}
};

struct FreqNode{
	int freq;
	map<string, CacheEntry*> entries;
};

class LFUCache{
public:
	CacheEntry* get(string key){
		if (m_map.find(key) == m_map.end()) return nullptr; // not found!

		return m_map[key]->value;
	}



private:
	unordered_map<string, list<Cacheentry>::iterator> m_map;
	list<FreqNode> m_FreqNodeCache;

	int m_capacity;
	int mutex;

}