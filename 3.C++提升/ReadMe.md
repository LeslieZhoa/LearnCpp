### C++编程提高
#### 模板
建立通用模具，大大提高复用性
1. 特点：
    - 不可直接使用，只是一个框架
    - 模板通用不是万能的
    - 利用模板编程叫 --> 泛型编程
2. 函数模板
    - 作用：建立一个通用函数，其函数返回值和形参类型可以不具体制定，用一个虚拟类型表示
    - 语法：
        ```c
        template<typename T>
        // templacte --> 声明创建模板
        // typename --> 表示其后面符号是一种数据类型，可用class代替
        // T --> 通用数据类型，名称可替换，通常为大写字母
        
        // 例子
        // 定义
        template<class T>
        void mySwap(T &a, T &b){
            T temp = a;
            a = b;
            b = temp;
        }
        
        // 调用
        // 第一种 自动类型推导
        int a = 10;
        int b = 20;
        mySwap(a,b); // 注a,b类型要一致
        
        // 第二种 显示制定类型
        mySwap<int>(a,b);
        
        
        // 注意 
        // 自动推导，必须推导出一致数据类型T,才能使用模板
        // 模板必须要确定出T数据类型，才可以使用
        template<class T>
        void func(){
            cout << "func调用" << endl;
        }
        
        // 调用
        func(); // 错误，无法确定T数据类型
        func<int>(); // 正确
        
        ```
    - 普通函数模板注意事项
        - [ ] 普通函数模板调用，可发生自动类型转换（隐式类型转换）
        - [ ] 函数模板调用时，如果利用自动类型推导，不会发生隐式类型转换
        - [ ] 如果利用显示制定类型方式，可发生隐式类型转换
        ```c
        template<class T>
        T myAdd(T a, T b){
            return a + b;
        }
        
        int a = 10;
        char c = 'c';
        myAdd(a,c) // 错误，不可发生隐式类型转换
        myAdd<int>(a,c) // 正确，可发生隐式类型转换
        ```
    - 普通函数与函数模板调用规则
        - [ ] 如果函数模板和普通函数都可实现，优先调用普通函数
        - [ ] 可通过空模板参数来强制调用模板函数
        - [ ] 函数模板也可重载
        - [ ] 若函数模板可产生更好匹配，优先调用函数模板
        ```c
        void myPrint(int a, int b){
            count << "调用普通函数" << endl;
        }
        
        template<class T>
        void myPrint(T a, T b){
            count << "调用函数模板" << endl;
        }
        
        int a = 10;
        int b = 10;
        myPrint(a,b); // 调用普通函数
        
        myPrint<>(a,b); // 通过空模板列表强制调用函数模板
        
        // 模板重载
        template<class T>
        void myPrint(T a, T b, T c){
            count << "调用重载函数模板" << endl;
        }
        
        char c1 = 'a';
        char c2 = 'b';
        myPrint(c1,c2); // 虽然普通函数也不报错，但调用的是更合适的函数模板
        ```
    - 模板局限性<br>
        例：模板判断两个类是否相等
        ```c
        // 光写判断相等模板函数可等无法判定自定义类型，需要具体化实现
        class Person{
        public:
            Person(string name, int age){
                this->m_Name = name;
                this->m_Age = age;
            }
            string m_Name;
            int m_Age;
        };
        
        template<class T>
        bool myCompare(T &a, T &b){
            if (a==b)
                return true;
            else
                return false;
        }
        // 还需要具体化Person版本的模板函数
        template<> bool myCompare(Person &p1,Person &p2){
            if (p1.m_Name == p2.m_Name && p1.m_Age == p2.m_Age)
                return true;
            else
                return false;
        }
        
        // 调用，利用模板具体化，可解决不能涵盖的自定义类型
        Person p1("Tom",16);
        Person p2("Jack",15);
        myCompare(p1,p2);
        ```
3. 类模板
    - 特点：建立一个通用类，其中成员数据类型可以不具体指定，用一个虚拟类型代表
    - 语法：
        ```c
        // template<typename T>
        // 类定义
        template<class NameType, class AgeType>
        class Person{
        public:
            Person(NameType name,  AgeType age){
                this->m_Name = name;
                this->m_Age = age;
            }
            NameType m_Name;
            AgeType m_Age;   
        };
        
        // 调用
        Person<string,int> p1("孙"，999)；
        ```
    - 类模板和函数模板区别
        - [ ] 类模板没有自动类型推导使用方式
        - [ ] 类模板在模板参数列表可以有默认参数
            ```c
            template<class NameType, class AgeType=int>
            class Person{
            public:
                Person(NameType name,  AgeType age){
                    this->m_Name = name;
                    this->m_Age = age;
                }
                NameType m_Name;
                AgeType m_Age;   
            };
            ```
    - 类模板成员函数创建时机
        - [ ] 普通类成员函数一开始就创建好
        - [ ] 类模板中成员函数因为不确定类型，在调用时才创建
    - 类模板对象做函数参数
        ```c
        template<class NameType, class AgeType=int>
        class Person{
        public:
            Person(NameType name,  AgeType age){
                this->m_Name = name;
                this->m_Age = age;
            }
            void showPerson(){
                cout << this->m_Name << " " << this->m_Age << endl;
            }
            NameType m_Name;
            AgeType m_Age;   
        };
        ```
        - [ ] 指定传入类型
            ```c
            void printPerson1(Person<string,int> &p){
                p.showPerson();
            }
            
            // 调用
            Person<string,int>p("孙",100);
            printPerson1(p);
            ```
        - [ ] 参数模板化
            ```c
            template<class T1,class T2>
            void printPerson2(Person<T1,T2> &p){
                p.showPerson();
            }
            
            // 调用
            Person<string,int>p("孙",100);
            printPerson2(p);
            ```
        - [ ] 整个类模板化
            ```c
            template<class T>
            void printPerson3(T &p){
                p.showPerson();
            }
            
            // 调用
            Person<string,int>p("孙",100);
            printPerson3(p);
            ```
    - 类模板与继承
        ```c
        template<class T>
        class Base{
        public:
            T m;
        };
        ```
        - [ ] 当子类继承是一个类模板，子类在声明时要指出父类T类型
            ```c
            class Son:public Base<int>{
                
            };
            ```
        - [ ] 如果不指定编译器无法给子类分配内存
        - [ ] 如果想灵活指出父类中T，子类也需为类模板
            ```c
            template<class T1,class T2>
            class Son2:public Base<T2>
            {
            public:
            T1 obj;
                
            };
            ```
    - 类模板成员函数类外实现
        ```c
        template<class T1, class T2>
        class Person{
        public:
            Person(T1 name,  T2 age);
            void showPerson();
            T1 m_Name;
            T2 m_Age;   
        };
        
        // 类外实现
        template<class T1, class T2>
        Person<T1,T2>::Person(T1 name, T2 age){
            this->m_Name = name;
            this->m_Age = age; 
        }
        
        template<class T1, class T2>
        void Person<T1,T2>::showPerson(){
            cout << this->m_Name << " " << this->m_Age << endl;
        }
        ```
    - 类模板分文件编写<br>
        存在问题是分文件可能链接不到
        - [ ] .h写函数声明，.cpp写函数定义，主程序调用导入```#include "Person.cpp"```,因为模板成员函数在调用时才创建
        - [ ] 将.h和.cpp内容放到一起，将后缀改为.hpp，主程序调用导入```#include "Person.hpp"```
    
    - 类模板与友元
        - [ ] 全局函数类内实现
            ```c
            template<class T1, class T2>
            class Person{
            friend void printPerson1(Person<T1,T2> p){
                cout << p.m_Name << " " << p.m_Age << endl;
            }
            public:
                Person(T1 name, T2 age){
                    this->m_Name = name;
                    this->m_Age = age; 
                }
            private:
                T1 m_Name;
                T2 m_Age;   
            };
            
            // 调用
            Person<string,int> p("Tom",20);
            printPerson1(p);
            ```
        - [ ] 全局函数类外实现<br>
            加空模板参数；需让编译器提前知道这个函数存在
            ```c
            template<class T1, class T2>
            class Person; // 提前知道有Person存在
            
            // 类外实现，提前知道函数存在
            template<class T1, class T2>
            void printPerson2(Person<T1,T2>p){
                cout << p.m_Name << " " << p.m_Age << endl;
            }
            
            template<class T1, class T2>
            class Person{
            
            public:
                Person(T1 name, T2 age){
                    this->m_Name = name;
                    this->m_Age = age; 
                }
            private:
                T1 m_Name;
                T2 m_Age;   
            };
            
            ```
#### STL
1. 特点
    - 标准模板库，广义上分容器，算法，迭代器；
    - 容器和算法之间通过迭代器无缝连接；
    - STL几乎所有代码都采用模板类或模板函数
2. 组件
    - 容器：各种数据结构
    - 算法：排序，查找，拷贝，遍历等算法
    - 迭代器：容器与算法之间胶合剂
    - 仿函数：行为类似函数，是类里的()重载，可作为算法某种策略
    - 适配器：一种用来修饰容器或仿函数或迭代器接口东西
    - 空间配置器：负责空间配置和管理
3. 迭代器
    - 作用：使算法可访问容器元素，又无需暴露该容器内部表示方式，每个容器都有自己专属迭代器，迭代器使用类似指针
    - 种类
        |种类 |功能 |支持运算 |
        |:-:|:-:|:-:|
        |输入迭代器 |对数据只读 |只读，支持++,++,!= | 
        | 输出迭代器|对数据只写 |只写，支持++ |
        | 前向迭代器|读写，并能向前推进迭代器 |读写，支持++,==,!= |
        | 双向迭代器|读写操作，并能向前向后推进迭代器 |读写，支持++,-- |
        | 随机访问迭代器|读写操作，可以跳跃式访问任意数据 | 读写，支持++,--,[n],-n,<,<=,>,>=|
        常用容器中迭代器种类为双向迭代器和随机访问迭代器
-----------------------------------------------------------
### 容器
- #### 序列式容器：强调值的排序，序列或容器中每个元素均有固定位置
    - #### string
        - [x] string和char*区别
            - char*是指针
            - string是一个类，类内封装char *,是对char *型的容器
        - [x] 特点：
            - string类内封装很多成员方法，如查找find,拷贝copy,删除delete,插入insert
            - string管理char* 所分配内存，不必担心复制越界和取值越界，由类内部负责
        - [x] 构造
            ```c
            #include<string>
            ```
            - ```string();``` --> 创建空字符
                ```c
                string s1;
                ```
            - ```string(const char * s);``` --> 使用字符s初始化
                ```c
                const char * str = "hello";
                string s2_1(str);
                string s2_2("hello");
                ```
            - ```string(const string & str);``` --> 使用一个string初始化
                ```c
                string s3(s2);
                ```
            - ```string(int n,char c)``` --> 使用n个字符c初始化
                ```c
                string s4(10,'c');
                ```
        - [x] 赋值  
            ```c
            // 第一种 string& operator=(const char * s);
            string s1;
            s1 = "hello";
            
            // 第二种 string& operator=(const string & s);
            string s2;
            s2 = s1;
            
            // 第三种 string& operator=(char c);
            string s3;
            s3 = 'a';
            
            // 第四种 string & assign(const char * s);
            string s4;
            s4.assign("hello");
            
            // 第五种 string & assign(const char * s, int n);
            // 把s前n个字符赋值
            string s5;
            s5.assign("hello",4);
            
            // 第六种 string & assign(const string & s);
            string s6;
            s6.assign(s5);
            
            // 第七种 string & assign(int n, char c); 
            // n个字符c
            string s7;
            s7.assign(10,'w');
            ```
        - [x] 拼接（尾部拼接）
            ```c
            string s1 = "我";
            // 第一种 string & operator+=(const char * str);
            s1 += "爱玩";
            
            // 第二种 string & operator+=(const char c);
            s1 += ':';
            
            // 第三种 string & operator+=(const string & str);
            string s2 = "LoL";
            s1 += s2;
            
            // 第四种 string & append(const char * s);
            s1.append("I LOVE");
            
            // 第五种 string & append(const char * s, int n);
            // 拼接前n个字符
            s1.append("I LOVE",3);
            
            // 第六种 string & append(const string & s);
            s1.append(s2);
            
            // 第七种 string & append(const string & s,int pos,int n);
            // 从s的pos位置连续n个字符拼接尾部
            s1.append(s2,1,2);
            ```
        - [x] 查找和替换
            - ```int find(const string & str,int pos=0) const;``` --> 查找str第一次出现位置，从pos开始查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int find(const char * s,int pos=0) const;``` --> 查找s第一次出现位置，从pos开始查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int find(const char * s,int pos=0,int n) const;``` --> 查找s前n个字符第一次出现位置，从pos开始查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int find(const char  s,int pos=0) const;``` --> 查找s字符第一次出现位置，从pos开始查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int rfind(const string & s,int pos=npos) const;``` --> 查找s最后一次出现出现位置，从pos开始往前查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int rfind(const char * s,int pos=npos) const;``` --> 查找s最后一次出现出现位置，从pos开始往前查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int rfind(const char * s,int pos=npos,int n) const;``` --> 查找s的前n个字符最后一次出现出现位置，从pos开始往前查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```int rfind(const char s,int pos=npos) const;``` --> 查找s字符最后一次出现出现位置，从pos开始往前查找，返回匹配字符串的第一个字符位置，若不存在返回-1
            
            - ```string & replace(int pos,int n,const string &s);``` --> 替换pos开始n个字符为s
            
            - ```string & replace(int pos,int n,const char * s);``` --> 替换pos开始n个字符为s
        - [x] 字符串比较<br>
            按字符串ASCII码值逐个对比，相等返回0；大于返回1；小于返回-1
            ```c
            int compare(const string & s) const;
            int compare(const char * s) const;
            ```
        - [x] 字符存取
            ```c
            // char & operator[](int n);
            string s = "hello";
            s[1];
            
            // char & at(int n);
            s.at(1);
            ```
        - [x] 插入删除
            - ```string & insert(int pos,const char * s);```
            
            - ```string & insert(int pos,const string & s);```
            
            - ```string & insert(int pos,int n ,const char c);``` --> 在指定位置插入n个字符c
            
            - ```string & erase(int pos,int n = npos);``` --> 删除从pos开始n个字符
        - [x] 子串
            - ```string substr(int pos=0,int n=npos) const;``` --> 返回由pos开始n个字符组成字符串
    - #### vector
        ```c
        #include<vector>
        ```
        - [x] 特点：可动态扩展，找更大内存空间，把原数据拷贝到新空间，释放掉原空间
        - [x] 迭代器指向
            - ```vector<T>::iterator v.begin()``` --> 指向第一个元素位置
            
            - ```vector<T>::iterator v.end()``` --> 指向最后一个元素下一个位置
            
            - ```vector<T>::iterator v.rbegin()``` --> 指向最后一个元素位置
            
            - ```vector<T>::iterator v.rend()``` --> 指向第一个元素前一个位置
        - [x] 构造
            - ```vector<T> v;``` --> 声明
            
            - ```vector(iterator beg, iterator end);``` --> 把迭代器[beg,end)区间值拷贝
            
            - ```vector(n,elem);``` --> 构造函数将n个elem拷贝
            
            - ```vector(const vector & vec);``` --> 拷贝构造函数
        - [x] 赋值
            - ```vector & operator=(const vector & vec);```
            
            - ```assign(iterator beg,iterator end);``` --> 将迭代器[beg,end)区间赋值
            
            - ```assign(n,elem);``` --> n个elem拷贝
            ```c
            vector<int> v;
            v = {1,2,3,4,5};
            ```
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```capacity()``` --> 容器容量
            
            - ```size()``` --> 返回容器元素个数
            
            - ```resize(int num)``` --> 重新指定容器长度，容器变长以默认值填充，变小则删除多余部分
            
            - ```resize(int num,elem)``` --> 重新指定容器长度，容器变长以elem填充，变小则删除多余部分
        - [x] 插入与删除
            - ```push_back(elem);``` --> 尾部插入elem
            
            - ```pop_back();``` --> 删除最后一个元素
            
            - ```insert(const_iterator pos,elem)``` --> 向迭代器指向位置pos插入元素elem
            
            - ```insert(const_iterator pos,int count ,elem)``` --> 迭代器指向位置pos插入count个元素elem
            
            - ```erase(const_iterator pos)``` --> 删除迭代器指向元素
            
            - ```erase(const_iterator start, const_iterator end)``` --> 删除迭代器从start到end之间元素
            
            - ```clear()``` --> 清空容器内元素
            
        - [x] 数据存取
            - ```at(int idx);```
            
            - ```operator[];```
            
            - ```front();``` --> 返回第一个元素
            
            - ```back();``` --> 返回最后一个元素
            
        - [x] 容器互换
            - 语法：```swap(vec);```
            - 实际用途 --> 收缩内存
                ```c
                vector<int> v;
                for (int i = 0; i < 1000; i++){
                    v.push_back(i);
                }
                v.resize(3); // v的capaticy不会减少
                
                vector<int>(v).swap(v); // v的capaticy会减少
                // vector<int>(v) --> 匿名对象，会创建size大小容器
                ```
        - [x] 预留空间
            - 用途：减少vector在动态扩展容量时的扩展次数
            - 语法:
                ```c
                reserve(int len); // 容器预留len个长度，预留位置不初始化，元素不可访问
                // 提前预留空间就可以不用每次不够就重新找新的空间
                ```
    - #### deque
        ```c
        #include<deque>
        ```
        - [x] 特点：
            - 双端数组
            - vector头部插入删除需移动元素，deque头尾都可插入删除
            - vector访问速度比deque快
        - [x] 内部原理
            - 内部有中控器，维护每段缓冲区中的内容，缓冲区存放真实数据
            - 中控器维护的是每个缓冲区地址，使得使用deque就像一片连续内存访问
        - [x] 构造
            - ```deque<T> d;``` --> 声明
            
            - ```deque(iterator beg, iterator end);``` --> 把迭代器[beg,end)区间值拷贝
            
            - ```deque(n,elem);``` --> 构造函数将n个elem拷贝
            
            - ```deque(const deque & deq);``` --> 拷贝构造函数
        - [x] 赋值
            - ```deque & operator=(const deque & deq);```
            
            - ```assign(iterator beg,iterator end);``` --> 将迭代器[beg,end)区间赋值
            
            - ```assign(n,elem);``` --> n个elem拷贝
           
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
            
            - ```resize(int num)``` --> 重新指定容器长度，容器变长以默认值填充，变小则删除多余部分
            
            - ```resize(int num,elem)``` --> 重新指定容器长度，容器变长以elem填充，变小则删除多余部分
        - [x] 插入与删除
            - ```push_back(elem);``` --> 尾部插入elem
            
             - ```push_front(elem);``` --> 头部插入elem
            
            - ```pop_back();``` --> 删除最后一个元素
            
             - ```pop_front();``` --> 删除第一个元素
            
            - ```insert(const_iterator pos,elem)``` --> 向迭代器指向位置pos插入元素elem,返回新数据的位置
            
            - ```insert(const_iterator pos,int count ,elem)``` --> 迭代器指向位置pos插入count个元素elem,无返回值
            
            - ```insert(iterator pos,iterator beg, iterator end)``` --> 向迭代器指向位置pos插入元素迭代器[beg,end)间的元素，无返回值
            
            - ```erase(const_iterator pos)``` --> 删除迭代器指向元素，返回下一个数据的位置
            
            - ```erase(const_iterator start, const_iterator end)``` --> 删除迭代器从start到end之间元素，返回下一个数据的位置
            
            - ```clear()``` --> 清空容器内元素
            
        - [x] 数据存取
            - ```at(int idx);```
            
            - ```operator[];```
            
            - ```front();``` --> 返回第一个元素
            
            - ```back();``` --> 返回最后一个元素
    - #### stack
        ```c
        #include<stack>
        ```
        - [x] 特点：先进后出，不允许遍历
        - [x] 构造
            - ```stack<T> stk;``` --> 声明
            
            - ```stack(const stack & stk);``` --> 拷贝构造函数
        - [x] 赋值
            - ```stack & operator=(const stack & stk);```
    
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
    
        - [x] 插入与删除
            - ```push(elem);``` --> 栈顶添加elem
            
            - ```pop();``` --> 栈顶移除一个元素
            
            - ```top();``` --> 返回栈顶元素
    - #### queue
        ```c
        #include<queue>
        ```
        - [x] 特点：先进先出，不允许遍历
        - [x] 构造
            - ```queue<T> que;``` --> 声明
            
            - ```queue(const queue & que);``` --> 拷贝构造函数
        - [x] 赋值
            - ```queue & operator=(const queue & que);```
    
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
    
        - [x] 插入与删除
            - ```push(elem);``` --> 队尾添加elem
            
            - ```pop();``` --> 队头移除一个元素
            
            - ```back();``` --> 返回最后一个元素
            
            - ```front();``` --> 返回第一个元素
            
- #### 关联式容器：二叉树结构，各元素之间没有严格物理顺序关系
    - #### list
        ```c
        #include<list>
        ```
        - [x] 特点：
            - 链表，由一系列结点构成
            - 动态存储分配，不会造成空间浪费溢出，可对任意位置快速插入或删除
            - 有数据域和指针域不是连续内存空间，迭代器支持前移和后移，属双向迭代器
            - 遍历速度慢，空间(指针域)时间(遍历)额外消耗大
            - 插入删除后原有迭代器不会发生改变，但vector会改变
            
        - [x] 构造
            - ```list<T> lst;``` --> 声明
            
            - ```list(iterator beg, iterator end);``` --> 把迭代器[beg,end)区间值拷贝
            
            - ```list(n,elem);``` --> 构造函数将n个elem拷贝
            
            - ```list(const list & lst);``` --> 拷贝构造函数
        - [x] 赋值
            - ```list & operator=(const list & lst);```
            
            - ```assign(iterator beg,iterator end);``` --> 将迭代器[beg,end)区间赋值
            
            - ```assign(n,elem);``` --> n个elem拷贝
            
            - ```swap(lst);``` --> 交换
           
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
            
            - ```resize(int num)``` --> 重新指定容器长度，容器变长以默认值填充，变小则删除多余部分
            
            - ```resize(int num,elem)``` --> 重新指定容器长度，容器变长以elem填充，变小则删除多余部分
        - [x] 插入与删除
            - ```push_back(elem);``` --> 尾部插入elem
            
             - ```push_front(elem);``` --> 头部插入elem
            
            - ```pop_back();``` --> 删除最后一个元素
            
             - ```pop_front();``` --> 删除第一个元素
            
            - ```insert(const_iterator pos,elem)``` --> 向迭代器指向位置pos插入元素elem,返回新数据的位置
            
            - ```insert(const_iterator pos,int count ,elem)``` --> 迭代器指向位置pos插入count个元素elem,无返回值
            
            - ```insert(iterator pos,iterator beg, iterator end)``` --> 向迭代器指向位置pos插入元素迭代器[beg,end)间的元素，无返回值
            
            - ```erase(const_iterator pos)``` --> 删除迭代器指向元素，返回下一个数据的位置
            
            - ```erase(const_iterator start, const_iterator end)``` --> 删除迭代器从start到end之间元素，返回下一个数据的位置
            
            - ```clear()``` --> 清空容器内元素
            
            - ```remove(elem)``` --> 删除所有与elem匹配元素
            
        - [x] 数据存取<br>
            迭代器只支持```it++;it--;```,不支持```it += 3; it = it + 1;```
            
            - ```front();``` --> 返回第一个元素
            
            - ```back();``` --> 返回最后一个元素
        - [x] 反转排序
            - ```reverse()``` --> 反转
            
            - ```sort()``` --> 排序
                ```c
                // 不支持随机访问迭代器，不可用标准算法，但内部提供一些算法
                list<int> l = {1,2,6,5,4};
                l.sort(); // 默认升序
                // 实现降序
                bool myCompare(int v1,int v2){
                    return v1 > v2;
                }
                
                l.sort(myCompare); // 降序
                ```
    - #### set/multiset
        ```c
        #include<set>
        ```
        - [x] 特点：
            - 所有元素惠子插入时自动排序
            - 底层用二叉树实现
            - set不允许有重复元素
            - multiset可以有重复元素
            
        - [x] 构造
            - ```set<T> st;``` --> 声明
            
            - ```set(const set & st);``` --> 拷贝构造函数
        - [x] 赋值
            - ```set & operator=(const set & st);```
            
            -  ```swap(st)```
           
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
       
        - [x] 插入与删除
            - ```insert(elem)``` --> 插入elem元素
            
            - ```erase(const_iterator pos)``` --> 删除迭代器指向元素，返回下一个数据的位置
            
            - ```erase(const_iterator start, const_iterator end)``` --> 删除迭代器从start到end之间元素，返回下一个数据的位置
            
            - ```clear()``` --> 清空容器内元素
            
            - ```erase(elem)``` --> 删除与elem匹配元素
            
        - [x] 查找和统计
            - ```find(key)``` --> 查找key是否存在，若存在返回该键元素迭代器，若不存在返回st.end()
            
            - ```count(key)``` --> 统计key元素个数
            
        - [x] set/multiset区别
            - set不可重复插值，multiset可以
            - set插入数据同时会返回插入结果，表示插入是否成功
                ```c
                set<int> s1;
                pair<set<int>::iterator,bool> ret = s1.insert(10);
                ```
            - multiset不会检测数据，因此可以插入重复数据
        - [x] 排序
            - 内置类型排序
                ```c
                // 自定义排序规则
                class MyCompare{
                public:
                    bool operator()(int a,int b) // 仿函数
                    {
                        return a > b;
                    }
                    
                };
                set<int,MyCompare> s2 = {1,4,6,3,0};
                for(auto v:s2){
                    cout << v << endl;
                }
                ```
            - 自定义类型，必须指定排序规则
                ```c
                class Person{
                public:
                    Person(string name,int age){
                        this->m_Name = name;
                        this->m_Age = age;
                    }
                    string m_Name;
                    int m_Age;
                };
                
                // 指定自定义类型排序规则
                class comparePerson{
                public:
                    bool operator()(const Person & p1, const Person & p2){
                        return p1.m_Age > p2.m_Age;
                    }
                };
                
                Person p1("刘",30);
                Person p2("关",28);
                Person p3("张",20);
                set<Person,comparePerson> s = {p1,p2,p3};
                ```
    - #### pair<br>
        无需导入头文件
        - [x] 功能：成对出现的数据，利用对组可以返回两个数据
        - [x] 创建方式
            ```c
            // 第一种
            pair<type, type> p ( value1, value2 );
            
            //第二种
            pair<type, type> p = make_pair( value1, value2 );
            ```
    - #### map/multimap
        ```c
        #include<map>
        ```
        - [x] 特点：
            - map所有元素都是pair
            - pair第一个元素为键值起到元素指引作用，第二个元素为value(实值)
            - 所有元素键值自动排序
            - 底层用二叉树实现】
            - 可以根据key值快速找到value
            - map不可以有重复key值，multimap可以有
            
        - [x] 构造
            - ```map<T1,T2> mp;``` --> 声明
            
            - ```mp(const map & mp);``` --> 拷贝构造函数
        - [x] 赋值
            - ```map & operator=(const map & mp);```
            
            -  ```swap(mp)```
           
        - [x] 容量大小
            - ```empty()``` --> 判断是否为空
            
            - ```size()``` --> 返回容器元素个数
       
        - [x] 插入与删除
            - ```insert(elem)``` --> 插入elem元素
                ```c
                map<int,int> m;
                // 第一种
                m.insert(pair<int,int>(1,10));
                
                // 第二种
                m.insert(make_pair(2,20));
                
                // 第三种
                m.insert(map<int,int>::value_type(2,20));
                
                // 第四种
                m[4] = 10;
                
                // 查找不存在的key会自动赋值为0或空字符等
                ```
            
            - ```erase(const_iterator pos)``` --> 删除迭代器指向元素，返回下一个数据的位置
            
            - ```erase(const_iterator start, const_iterator end)``` --> 删除迭代器从start到end之间元素，返回下一个数据的位置
            
            - ```clear()``` --> 清空容器内元素
            
            - ```erase(key)``` --> 删除键值为key的元素
            
        - [x] 查找和统计
            - ```find(key)``` --> 查找键值为key是否存在，若存在返回该键只元素迭代器，若不存在返回mp.end()
            
            - ```count(key)``` --> 统计键值为key元素个数
            
        - [x] 排序
            ```c
            // 自定义排序规则
            class MyCompare{
            public:
                bool operator()(int a,int b) // 仿函数
                {
                    return a > b;
                }
                
            };
            map<int,int,MyCompare> m;
            m.insert<make_pair(1,10));
            m.insert<make_pair(2,10));
            ```
### 函数
1. 函数对象<br>
    重载() --> 也叫仿函数
    - 特点：
        - 可以像普通函数调用
        - 函数对象可以有自己状态
        - 函数对象可以作为参数传递
    ```c
    // 作为参数传递
    class MyPrint{
    public:
        void operator()(string test){
            cout << test << endl;
        }
    };
    
    // 调用
    void doPrint(MyPrint & mp,string test){
        mp(test);
    }
    ```
2. 谓词<br>
    返回bool类型仿函数叫谓词
    - operator()接受一个参数叫一元谓词
        ```c
        // 返回比5大的数
        class GreaterFive{
        public:
            bool operator()(int val){
                return val > 5;
            }
        };
        
        ```
    - operator()接受两个参数叫二元谓词
        ```c
        class MyPare{
        public:
            bool operator()(int v1, int v2){
                return v1 > v2;
            }
        };
        ```
3. 内建函数对象
    ```c
    #include<functional>
    ```
    - 算术仿函数
        - [x] ```template<class T> T plus<T>``` --> 加法仿函数
            ```c
            plus<int>p;
            p(10,20); // 10+20
            ```
            
        - [x] ```template<class T> T minus<T>``` --> 减法仿函数
        
        - [x] ```template<class T> T multiplies<T>``` --> 乘法仿函数
        
        - [x] ```template<class T> T divides<T>``` -->除法仿函数
        
        - [x] ```template<class T> T modulus<T>``` --> 取模仿函数
        
        - [x] ```template<class T> T negate<T>``` --> 取反仿函数
            ```c
            negate<int> n1;
            n1(50); // 对50取反
            ```
    - 关系仿函数
        - [ ] ```template<class T> bool equal_to<T>``` --> 等于
        
        - [ ] ```template<class T> bool not_equal_to<T>``` --> 不等于
        
        - [ ] ```template<class T> bool greater<T>``` --> 大于
        
        - [ ] ```template<class T> bool greater_equal<T>``` --> 大于等于
        
        - [ ] ```template<class T> bool less<T>``` --> 小于
        
        - [ ] ```template<class T> bool less_equal<T>``` --> 小于等于
    - 逻辑仿函数
        - [ ] ```template<class T> bool logical_and<T>``` --> 逻辑与
        
        - [ ] ```template<class T> bool logical_or<T>``` --> 逻辑或
        
        - [ ] ```template<class T> bool logical_not<T>``` --> 逻辑非
        
### 算法
- #### 质变算法：运算过程中更改区间内元素内容
    - #### 转换transform<br>
        相当于python中的map,以某种规则搬运容器到另一容器中
        ```c
        #include<algorithm>
        ```
        - [x] 语法：
            ```c
            transform(iterator beg1,iterator end1,iterator beg2, _func);
            // beg1 源开始迭代器
            // end1 源结束迭代器
            // beg2 目标容器开始迭代器
            // _func 函数或函数对象 
            ```
            
        - [x] 示例
            ```c
            #include<algorithm>
            #include<vector>
            #include<iostream>
            using namespace std;
            class Transform{
            publuc:
                int operator()(int v){
                    return v + 100;
                }
            };
            
            vector<int> v ={1,2,3,4,5,6,7,8,9,20}
            vector<int>vTarget;
            vTarget.resize(v.size()); //目标容器要提前开辟空间
            transform(v.begin(),v.end(),vTarget.begin(),Transform());
            ```
- #### 非质变算法：不更改区间内元素
    - #### 遍历for_each
        ```c
        #include<algorithm>
        ```
        - [x] 语法：
            ```c
            for_each(iterator beg,iterator end,_func);
            // beg 开始迭代器
            // end 结束迭代器
            // _func 函数或函数对象
            ```
        - [x] 示例
            ```c
            void print01(int val){
                cout << val << " ";
            }
            
            class print02{
            public:
                void operator()(int val){
                    cout << val << " ";
                }
            };
            
            vector<int> v = {1,6,5,3,8,9};
            for_each(v.begin(),v.end(),print01); // 普通函数
            
            for_each(v.begin(),v.end(),print02()); // 仿函数
            ```
    - #### 查找与统计<br>
        自定义类型需重载==
        ```c
        #include<algorithm>
        ```
        - __find__
            - [x] 语法：
                ```c
                find(iterator beg,iterator end,value);
                // beg 开始迭代器
                // end 结束迭代器
                // value 要查找的值
                
                // 按值查找，找到返回指定位置迭代器，找不到返回结束迭代器位置
                ```
            - [x] 示例
                ```c
                // 内置类型查找
                vector<int> v = {1,2,3,4,5};
                auto it = find(v.begin(),v.end(),5);// 查找元素中是否有5
                
                if (it == v.end()){
                    cout << "没找到！" << endl;
                }
                
                // 自定义类型查找，必须重载==
                class Person{
                public:
                    Person(string name, int age){
                        this->m_Name = name;
                        this->m_Age = age;
                    }
                    
                    bool operator==(const Person & p){
                        if (this->m_Name == p.m_Name && this->m_Age == p.m_Age){
                            return true;
                        }
                        else
                            return false;
                    }
                    string m_Name;
                    int m_Age
                };
                
                Perosn p1("aa",16);
                Perosn p2("bb",17);
                
                vector<Person> v = {p1,p2};
                find(v.begin(),v.end(),p1);
                
                ```
        - __find_if__
            - [x] 语法：
                ```c
                find_if(iterator beg,iterator end,_Pred);
                // beg 开始迭代器
                // end 结束迭代器
                // _Pred 函数或谓词，返回bool类型
                
                // 按条件查找，找到返回第一次找到位置迭代器，找不到返回结束迭代器位置
                ```
            - [x] 示例
                ```c
                class Compare{
                public:
                    bool operator()(int val){
                        return val > 5;
                    }
                };
                
                bool compare(int val){
                    return val > 5;
                }
                
                vector<int> v = {1,4,8,9,10};
                auto res1 = find_if(v.begin(),v.end(),compare); // 普通函数
                
                auto res1 = find_if(v.begin(),v.end(),Compare()); // 仿函数
                ```
        - __adjacent_find__
            - [x] 语法：
                ```c
                find_if(iterator beg,iterator end,);
                // beg 开始迭代器
                // end 结束迭代器
                
                // 查找是否有相邻重复元素，找到返回相邻元素第一个位置迭代器，找不到返回结束迭代器位置
                ```
        - __binary_search__
            - [x] 语法：
                ```c
                binary_search(iterator beg,iterator end,value);
                // beg 开始迭代器
                // end 结束迭代器
                // value 要查找的元素
                
                // 二分查找(元素有序排列)，找到返回元素第一次出现位置迭代器，找不到返回结束迭代器位置
                ```
         - __count__
            - [x] 语法：
                ```c
                count(iterator beg,iterator end,value);
                // beg 开始迭代器
                // end 结束迭代器
                // value 要统计的元素
                
                // 返回value出现次数
                ```
        - __count_if__
            - [x] 语法：
                ```c
                count_if(iterator beg,iterator end,_Pred);
                // beg 开始迭代器
                // end 结束迭代器
                // _Pred 所满足的函数或谓词
                
                // 返回满足_Pred条件的元素次数
                ```  
    - #### 排序
        ```c
        #include<algorithm>
        ```
        - __sort__
            - [x] 语法：
                ```c
                sort(iterator beg,iterator end,_Pred);
                // beg 开始迭代器
                // end 结束迭代器
                // _Pred 排序方法，若不指定，默认升序
                
                // 按指定方式排序
                ```
            - [x] 示例
                ```c
                // 内置类型查找
                #include<vector>
                #include<functional>
                #include<iostream>
                using namepace std;
                
                vector<int> v = {1,2,3,4,5};
                sort(v.begin(),v.end(),greater<int>());
                ```
        - __random_shuffle__
            - [x] 语法：
                ```c
                random_shuffle(iterator beg,iterator end);
                // beg 开始迭代器
                // end 结束迭代器
                
                // 随机打乱顺序
                ```
        - __merge__
            - [x] 语法：
                ```c
                merge(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dst);
                // beg1 第一个合并容器开始迭代器
                // end1 第一个合并容器结束迭代器
                // beg2 第二个合并容器开始迭代器
                // end2 第二个合并容器结束迭代器
                // dst  目标容器开始迭代器
                
                // 把两容器合并，注两容器必须有序，且排序方式一致，合并之后容器也是有序的
                ```
            - [x] 示例
                ```c
                vector<int> v1 = {1,2,4,5,6};
                vector<int> v2 = {2,5,7,10};
                vector<int> v3;
                v3.resize(v1.size()+v2.size());
                merge(v1.begin(),v1.end(),v2.begin(),v2.end(),v3.begin());
                ```
        - __reverse__
            - [x] 语法：
                ```c
                reverse(iterator beg,iterator end);
                // beg 开始迭代器
                // end 结束迭代器
                
                // 将容器内元素反转
                ```
    - #### 拷贝替换
        ```c
        #include<algorithm>
        ```
        - __copy__
            - [x] 语法：
                ```c
                copy(iterator beg,iterator end,iterator dst);
                // beg 开始迭代器
                // end 结束迭代器
                // dst 目标开始迭代器
                
                // 将源容器区间拷贝，是深拷贝
                ```
        - __copy_if__<br>
            相当于python中的filter
            - [x] 语法：
                ```c
                copy(iterator beg,iterator end,iterator dst,_Pred);
                // beg 开始迭代器
                // end 结束迭代器
                // dst 目标开始迭代器
                // _Pred 满足条件函数
                
                // 只拷贝满足条件元素
                ```
        - __replace__
            - [x] 语法：
                ```c
                replace(iterator beg,iterator end,old_value,new_value);
                // beg 开始迭代器
                // end 结束迭代器
                // old_value 所要替换值
                // new_value 替换的值
                
                // 替换区间内的旧元素，所有满足都替换
                ```
        - __replace_if__
            - [x] 语法：
                ```c
                replace(iterator beg,iterator end,_Pred,new_value);
                // beg 开始迭代器
                // end 结束迭代器
                // _Pred 所满足条件
                // new_value 替换的值
                
                // 替换区间内满足条件的旧元素，所有满足都替换
                ```    
        - __swap__
            - [x] 语法：
                ```c
                swap(container c1, container c2);
                // 交换两容器元素，容器类型保持一致
                ```    
    - #### 算术生成算法
        ```c
        #include<numeric>
        ```
        - __accamulate__<br>
            相当于python中的reduce
            - [x] 语法：
                ```c
                accamulate(iterator beg,iterator end,value,_Pred);
                // beg 开始迭代器
                // end 结束迭代器
                // value 累计的初始值
                // _Pred 元素经过函数再累加，默认无
                
                // 将元素处理后累加
                ```
        - __fill__
            - [x] 语法：
                ```c
                fill(iterator beg,iterator end,value);
                // beg 开始迭代器
                // end 结束迭代器
                // value 填充元素
                
                // 将容器指定区间添加元素,
                ```
        - __set_intersection__
            - [x] 语法：
                ```c
                set_intersection(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dst)
                // beg1 第一个合并容器开始迭代器
                // end1 第一个合并容器结束迭代器
                // beg2 第二个合并容器开始迭代器
                // end2 第二个合并容器结束迭代器
                // dst  目标容器开始迭代器
                
                // 求两个容器交集，两个集合必须有序，返回交集的尾指针end()
                ```
        - __set_union__
            - [x] 语法：
                ```c
                set_union(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dst)
                // beg1 第一个合并容器开始迭代器
                // end1 第一个合并容器结束迭代器
                // beg2 第二个合并容器开始迭代器
                // end2 第二个合并容器结束迭代器
                // dst  目标容器开始迭代器
                
                // 求两个容器并集，两个集合必须有序，返回交集的尾指针end()
                ```
        - __set_difference__<br>
            v1和v2差集 --> v1中不是交集的部分
            - [x] 语法：
                ```c
                set_difference(iterator beg1,iterator end1,iterator beg2,iterator end2,iterator dst)
                // beg1 第一个合并容器开始迭代器
                // end1 第一个合并容器结束迭代器
                // beg2 第二个合并容器开始迭代器
                // end2 第二个合并容器结束迭代器
                // dst  目标容器开始迭代器
                
                // 求两个容器差集，两个集合必须有序，返回交集的尾指针end()
                ```
-----------------------------------
### 其他
- ```using namespace std;``` --> 可以使用std下面的所有函数和类
#### C++11特性
1. __基于范围for循环__
    - 作用<br>
        类似python的for v in d:
    - 例子
        ```c
        int nArr[5] = {1,2,5,7,8};
        for (int &x : nArr){
            x *= 2;
        }
        ```
2. __自动推断类型__
    - [ ] auto
        - 作用<br>
            - 自动推断数据类型,
            - 声明的变量必须初始化，
            - 不能用于函数参数，
            - 不能用于数组类型推导，
            - 函数和模板参数不能被声明为auto，
            - 可以用于函数返回值
        - 例子
            ```c
            auto i = 1;
            
            
            vector<int> v(10,6);
            auto it = v.begin();
            
            
            int func(){
                return 0
            }
            auto v = func();
            ```
    - [ ] decltype
        - 作用<br>
            对表达式类型进行推导
        - 例子
            ```c
            const std::vector<int> v(1);
            auto c = 0;           // c 的类型是 int
            auto d = c;           // d 的类型是 int
            // 如果表达式e是一个变量，那么就是这个变量的类型。
            decltype(c) e;        // e 的类型是 int, 因为 c 的类型是int
            
            
            // 如果表达式e是一个函数，那么就是这个函数返回值的类型。
            decltype(c+d) f;        // f 的类型是 int, 因为 c+d 的类型是int
            // 如果不符合1和2，如果e是左值，类型为T，那么decltype(e)是T&；如果是右值，则是T。
            decltype(v[0]) b = 1; // b 的类型是 const int&, 因为函数的返回类型是
                                  // std::vector<int>::operator[](size_type) const
                          
            decltype((c)) g = c;  // g 的类型是 int&, 因为 (c) 是左值
            
             decltype(0) h;  // h 的类型是 int, 因为 0 是右值
    
            ```
3. __后置返回类型__
    - 作用<br>
        将返回类型后置
    - 例子
        
        ```c
        // 普通函数例子
        auto getSum(int a, int b)->int{
            return a + b
        }
        
        // auto decltype联合使用处理模板
        template <typename T1, typename T2>  
        auto compose(T1 t1, T2 t2) -> decltype(t1 + t2)     //返回值后置的占位符
        {  
           return t1+t2;  
        }  
        auto v = compose(2, 3.14); // v's type is double 
        ```
4. __匿名函数 Lambda__
    - 作用<br>
        对匿名函数的支持
    - 语法<br>
        ```[capture](parameters) mutable ->return-type{statement}```
        
        - [capture]：捕捉列表。捕捉列表总是出现在Lambda函数的开始处
        
        - (parameters)：参数列表。与普通函数的参数列表一致。如果不需要参数传递，则可以连同括号“()”一起省略;
        
        - mutable：mutable修饰符。默认情况下，Lambda函数总是一个const函数，mutable可以取消其常量性。在使用该修饰符时，参数列表不可省略（即使参数为空）;
        
        - ->return-type：返回类型。用追踪返回类型形式声明函数的返回类型。我们可以在不需要返回值的时候也可以连同符号”->”一起省略。此外，在返回类型明确的情况下，也可以省略该部分，让编译器对返回类型进行推导;
        
        - {statement}：函数体。内容与普通函数一样，不过除了可以使用参数之外，还可以使用所有捕获的变量。
    - [capture]捕捉列表可获取参数
        - []不捕获任何变量。

        - [&]捕获外部作用域中所有变量，并作为引用在函数体中使用（按引用捕获）。
        
        - [=]捕获外部作用域中所有变量，并作为副本在函数体中使用(按值捕获)。
        
        - [=,&foo]按值捕获外部作用域中所有变量，并按引用捕获foo变量。
        
        - [bar]按值捕获bar变量，同时不捕获其他变量。
        
        - [this]捕获当前类中的this指针，让lambda表达式拥有和当前类成员函数同样的访问权限。如果已经使用了&或者=，就默认添加此选项。捕获this的目的是可以在lamda中使用当前类的成员函数和成员变量。
    - 例子
        ```c
         class A
         {
         public:
             int i_ = 0;
             
             void func(int x,int y){
                 auto x2 = [=] { return i_ + x + y; };               //OK
                 auto x3 = [&] { return i_ + x + y; };               //OK
                 auto x4 = [this] { return i_; };                        //OK
                 auto x5 = [this] { return i_ + x + y; };            //error,没有捕获x,y
                 auto x6 = [this, x, y] { return i_ + x + y; };    //OK
                 auto x7 = [this] { return i_++; };                   //OK
         };
         
         int a=0 , b=1;
         auto f2 = [&] { return a++ };                      //OK
         auto f3 = [=] { return a; };                       //OK
         auto f4 = [=] {return a++; };                      //error,a是以复制方式捕获的，无法修改
         auto f2 = [=] () mutable { return a++; };          //OK
         auto f6 = [a, &b] { return a + (b++); };           //OK
         auto f7 = [=, &b] { return a + (b++); };           // OK
         
         // 应用实例
         vector<int> v = {1,2,3,4,5};
         for_each( v.begin(), v.end(), [](int x){ if (x > 2){cout << x << endl;}});

        ```
5. __重写覆盖__
    - final <br>
        禁止继承
        ```c
        struct B1 final { };
        // B1不可以被其他继承
        
        struct B2
        {
            virtual void f() final {} // final 函数
        };
        // f() 不可以被子类重写
        ```
    - override<br>
        要配合virtual使用，override保留字表示当前函数重写了基类的虚函数。
        - 作用<br>
            避免函数名参数类型写错
        - 例子
            ```c
            struct B4
            {
                virtual void g(int) {}
            };
            
            struct D4 : B4
            {
                virtual void g(int) override {} // OK
                virtual void g(double) override {} // Error
            };
            ```
6. __指针__
    - nullptr空指针<br>
        NULL通常在C语言中预处理宏定义为(void*)0或者0，这样0就有int型常量和空指针的双重身份。
        ```c
        void foo(int n);
        void foo(char* cArr);
        ```
        - 特点：<br>
        上面声明了两个重载函数，当我调用foo(NULL)，编译器将会调用foo(int)函数，而实际上我是想调用foo(char*)函数的。为了避免这个歧义，C++11重新定义了一个新关键字nullptr，充当单独空指针常量。
    - 智能指针
        - shared_ptr，基于引用计数的智能指针，会统计当前有多少个对象同时拥有该内部指针；当引用计数降为0时，自动释放
        - weak_ptr，基于引用计数的智能指针在面对循环引用的问题将无能为力，因此C++11还引入weak_ptr与之配套使用，weak_ptr只引用，不计数
        - unique_ptr:遵循独占语义的智能指针，在任何时间点，资源智能唯一地被一个unique_pt所占有，当其离开作用域时自动析构。资源所有权的转移只能通过std::move()而不能通过赋值
7. __模板别名__<br>
    ```c
    template <typename First, typename Second, int Third>
    class SomeType; 
    
    template <typename Second>
    using TypedefName = SomeType<OtherType, Second, 5>;
    
    //这种using语法也可以用来定义类型的别名:　　
    typedef void (*FunctionType)(double);  // 老式语法
    
    using FunctionType = void (*)(double); // 新式语法
    ```
8. 线程支持
    - joinable(): 判断线程对象是否可以join,当线程对象被析构的时候如果对象``joinable()==true``` 会导致```std::terminate```被调用。
    - join(): 阻塞当前进程(通常是主线程)，等待创建的新线程执行完毕被操作系统回收。
    - detach(): 将线程分离，从此线程对象受操作系统管辖。
    - 线程管理函数
        | 函数名|作用 |
        |:-:|:-:|:-:|
        | get_id|返回当前线程id |
         | yield|告知调度器运行其他线程，可用于当前处于繁忙的等待状态。 |
         | sleep_for| 指定的一段时间内停止当前线程的执行|
         |sleep_until |停止当前线程的执行直到指定的时间点|
    ```c
    // thread example
    #include <iostream>       // std::cout  std::cin
    #include <thread>         // std::thread
    void foo()
    {
        // do stuff...
        for(int i = 0; i < 100; ++i)
        {
            cout << "foo()  i: " << i << "\n";
        }
    }
    void bar(int x)
    {
        // do stuff...
        for(int j = x; j < 200; ++j)
        {
            cout << "bar()  j: " << j << "\n";
        }
    }
    int main()
    {
        std::cout << "main, foo and bar now execute concurrently...\n\n";
        std::thread first(foo);     // spawn new thread that calls foo()
        std::thread second(bar, 100);  // spawn new thread that calls bar(0)
        
        // synchronize threads:
        first.join();                // pauses until first finishes
        second.join();               // pauses until second finishes
        std::cout << "foo and bar completed.\n\n";
        std::cin.get();
        return 0;
    }
    ```
9. 元组tuple
    ```c
    #include<iostream>
    #include<stdlib.h>
    #include<tuple>
     
    using namespace std;
    int main(){
    	auto tp=make_tuple(12,"name","note");
    	cout<<get<0>(tp)<<","<<get<1>(tp)<<","<<get<2>(tp)<<endl;
    	cout<<tuple_size<tuple<int,string,string>>::value<<endl;
     
    	return 0;
    }
    ```
    
    ```c
    #include <tuple>
    #include <iostream>
    #include <string>
    #include <stdexcept>
     
    std::tuple<double, char, std::string> get_student(int id)
    {
        if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
        if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
        if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
        throw std::invalid_argument("id");
    }
     
    int main()
    {
        auto student0 = get_student(0);
        std::cout << "ID: 0, "
                  << "GPA: " << std::get<0>(student0) << ", "
                  << "grade: " << std::get<1>(student0) << ", "
                  << "name: " << std::get<2>(student0) << '\n';
     
        double gpa1;
        char grade1;
        std::string name1;
        std::tie(gpa1, grade1, name1) = get_student(1);
        std::cout << "ID: 1, "
                  << "GPA: " << gpa1 << ", "
                  << "grade: " << grade1 << ", "
                  << "name: " << name1 << '\n';
     
    }
    ```
#### 函数接收不定长参数列表
- 参数作用
    ```c
    //可变参数标准宏头文件
    #include "stdarg.h"
     
    //申明va_list数据类型变量pvar，该变量访问变长参数列表中的参数。
    va_list pvar;
     
    //宏va_start初始化变长参数列表。pvar是va_list型变量，记载列表中的参数信息。
    //parmN是省略号"..."前的一个参数名，va_start根据此参数，判断参数列表的起始位置。
    va_start(pvar, parmN);
     
    //获取变长参数列表中参数的值。pvar是va_list型变量，type为参数值的类型，也是宏va_arg返回数值的类型。
    //宏va_arg执行完毕后自动更改对象pvar，将其指向下一个参数。
    va_arg(pvar, type);
     
    //关闭本次对变长参数列表的访问。
    va_end(pvar);
    ```
- 例子
    ```c
    #include "stdarg.h"
    using namespace std;
    #include<iostream>
    
    int sum(int count, ...)
    {
    	int sum_value = 0;
    
    	va_list args;
    	va_start(args, count);
    	while (count--)
    	{
    		sum_value += va_arg(args, int);
    	}
    	va_end(args);
    
    	return sum_value;
    }
    
    int main()
    {
    	cout << sum(5, 1, 2, 3, 4, 5) << endl;//输出15
    	system("pause");
    	return 0;
    }
    ```