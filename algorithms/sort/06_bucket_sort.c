
桶排序的原理是将数组分到有限数量的桶中，再对每个桶子再分别排序（有可能再使用别的排序算法或是以递归方式继续使用桶排序进行排序），最后将各个桶中的数据有序的合并起来。

排序过程：假设待排序的一组数统一的分布在一个范围中，并将这一范围划分成几个子范围，也就是桶将待排序的一组数，
分档规入这些子桶，并将桶中的数据进行排序将各个桶中的数据有序的合并起来

桶排序本质就是用 bitset 来排序

void bucketSort(float arr[], int n) {
    // 1) Create n empty buckets
    vector<float> b[n];

    // 2) Put array elements in different buckets
    for (int i=0; i<n; i++) {
       int bi = n*arr[i]; // Index in bucket
       b[bi].push_back(arr[i]);
    }

    // 3) Sort individual buckets
    for (int i=0; i<n; i++)
       sort(b[i].begin(), b[i].end());

    // 4) Concatenate all buckets into arr[]
    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < b[i].size(); j++)
          arr[index++] = b[i][j];
}