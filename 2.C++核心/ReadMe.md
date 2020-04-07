### C++编程核心
#### 内存分区模型
1. 意义
    不同区域存放数据，赋予不同生命周期，给我们更大灵活编程
2. 分区种类<br>
    - 在程序编译后，生成了exe可执行程序，未执行该程序前
        1. 代码区
            - 存放内容<br>
                存放CPU执行机器指令，即函数二进制代码，由操作系统管理
            - 特点：<br>
                - [ ] 共享：内存只有一份代码即可
                - [ ] 只读：防止修改
        2. 全局区<br>
            - 存放内容<br>
                - [ ] 全局变量和静态变量存放于此（普通变量加static为静态变量）
                - [ ] const修饰全局常量和字符串常量存放于此
            - 特点<br>
                该区域数据在程序结束后由操作系统释放
    - 程序运行后的区域
        1. 栈区<br>
            - 存放内容<br>
                存放函数参数值，局部变量等，形参
            - 特点<br>
                由编译器自动分配释放
            - 注意事项<br>
                不要返回局部变量地址，栈区开辟数据会由编译器自动释放
        2. 堆区
            - 存放内容<br>
                由new创建开辟内存
                ```c
                // 语法： new 返回该数据类型指针
                
                // 1.开辟新值
                int * p = new int (10); //赋值为10，p为指针，需解引用*p值为10
                // 释放内存
                delete p;
                
                // 2. 开辟数组
                int * arr = new int[10];
                // 释放
                delete[] arr;
                
                ```
            - 特点<br>
                由程序员分配，若程序员不释放，程序结束时由操作系统回收
#### 引用
&nbsp;&nbsp;&nbsp;给变量起别名
1. 实现
    ```c
    // 语法：数据类型 &别名 = 原名;
    int a = 10;
    int &b = a;
    ```
2. 注意事项<br>
    - [ ] 必须初始化；
    - [ ] 初始化后不可改变，但值可改变即不可以继续跟别人名，但可以改内容
        ```c
        int a = 10;
        int &b = a;
        
        b = 20; // 这是正确的
        
        // 下面这个是不对的
        int c = 20;
        &b = c; // 不行
        int &b; // 也不行
        ```
3. 引用做函数参数
    - [ ] 作用:函数传参时，可利用引用技术让形参修饰实参，简化指针修改实参
        ```
        // 定义函数
        int swap(int &a, int &b){}
        
        // 调用
        swap(a,b); // 若函数有修改值功能，那么实参值也会改变
        
        ```
    - [ ] 引用做函数返回值<br>
        注意不要返回局部变量引用
        ```c
        // 用法：函数调用作为左值
        
        // 定义函数
        int & test(){
            static int a = 10;
            return a;
        }
        
        // 调用，可以这么玩
        test() = 1000;
        
        ```
4. 引用本质<br>
    内部实现指针常量
    - [ ] 指针指向不可改
    - [ ] 指针指向值可改
5. 常量引用
    - [ ] 作用：修饰形参，防止误操作
    - [ ] 注意：引用必须引一块合法内存空间
        ```c
        // 下列是错误的
        int & ref = 10;
        ```
    - [ ] 加上const变为常量，只读不可修改
        ```c
        const int & ref = 10; // 这样是对的
        
        // 正常常量引用
        int temp = 10;
        const int & ref = temp;
        
        // 但是temp依然可以更改
        ```
#### 函数提高
1. 默认参数
    - [ ] 语法
        ```c
        // 语法：返回值类型 函数名(形参=默认值){}
        int func(int a,int b = 20;int c = 30){}
        ```
    - [ ] 注意<br>
        默认参数后面必须还是默认参数，函数声明和函数定义只能有一个有默认参数
2. 占位参数
    - [ ] 作用：占位参数用来占位，调用函数时必须填补该位置
    - [ ] 语法
        ```c
        // 语法： 返回值类型 函数名(数据类型){}
        void func(int a, int){}
        
        //占位参数可以有默认参数
        void fucn(int a, int = 10){}
        ```
3. 函数重载
    - 特点<br>
        函数名相同，参数不同
        - [ ] 同一作用域下
        - [ ] 函数名相同
        - [ ] 函数参数类型不同或个数不同或顺序不同
        - [ ] 注：*__函数返回值不可作为函数重载条件__*，即返回值类型不同，不可以重载
    - 注意
        - [ ] 引用有无const作为重载条件
            ```c
            // 定义
            void func(const int & a){}
            // 调用
            func(10);
            
            //定义
            void func(int & a){}
            //调用
            int a = 10;
            func(a);
            ```
        - [ ] 默认参数发生重载易混淆
            ```c
            void func(int a,int b = 10) {}
            void func(int a){}
            
            // 调用下列函数会出错
            func(10);
            ```
---------------------------------------
### 类和对象
__具有相同性质的对象，我们可抽象为类__
#### 封装
1. 意义<br>
    - 将属性和行为作为一个整体，表现生活各种事物，将属性和行为加以权限控制
    - 类中属性和行为都称为成员
    - 属性叫成员属性，又叫成员变量
    - 行为叫成员函数，又叫成员方法
        ```c
        语法：class 类名 {访问权限:属性/行为};
        ```
2. 不同权限
    - 种类
        - [ ] 公共权限public --> 成员类内可访问，类外也可访问
        - [ ] 保护权限protected --> 成员类内可访问，类外不可访问，子类可访问
        - [ ] 私有权限private --> 成员类内可访问，类外不可访问，子类也不可访问
    - 小例子
        ```c
        class Person{
        public:
            string m_Name;
        protected:
            string m_Car;
        private:
            int m_Pass;
        };
        ```
3. struct 和 class区别<br>
    - struct 默认权限public
    - class 默认权限private
4. 成员属性私有化
    - 优点
        - [ ] 可以自己控制读写权限
        - [ ] 对于写权限，可以检测数据有效性
5. 类多文件写入
    ```
    1.创建.h文件，例person.h
        #pragma once --> 防止头文件已包含
        只写入成员函数和变量声明
    2.创建.cpp，例person.cpp
        #include "person.h" --> 倒入头文件
        void Person::sex(int x){} --> 写具体函数
        其中Person::表示类内的成员，是.h定义的类名
    ```
#### 对象
1. 对象初始化和清理
    - 实现<br>
        由编译器自动调用，编译器提供构造函数和析构函数的空实现
    - 构造函数<br>
        创建对象时，为对象成员属性赋值
        - [ ] 特点
            - 构造函数没有返回值，不写void
            - 函数名与类名相同
            - 构造函数可以有参数，所以可以重载
            - 程序在调用对象时自动调用，只调用一次
        - [ ] 不同类别构造函数
            1. 普通构造
                - 构造方法
                    - 无参构造
                    - 有参构造
                    ```c
                    class Person{
                    public:
                        
                        // 无参构造
                        Person(){
                            cout << "Person无参构造调用" << endl;
                        }
                        
                        // 有参构造
                        Peroson(int a){
                            cout << "Person有参构造调用" << endl;
                        }
                    }
                    ```
                - 调用方法
                    - 括号法
                         ```c
                        // 括号法
                        Person p1; // 无参
                        Person p2(10); //有参
                        
                        // 调用默认构造函数不要用()
                        Person p1(); //不可以用作构造函数调用，会误被认为函数声明
                        ```
                    - 显示法
                        ```c
                        // 显示法
                        Person p1 = Person();
                        Person p2 = Person(10);
                        
                        // Person(10) --> 匿名对象
                        // 特点是当执行结束后，系统会立即回收匿名对象
                        ```
                    - 隐式转换法
                        ```c
                        Person p4 = 10; // 等价于Person p4 = Person(10);
                        ```
                       
            2. 拷贝构造
                ```c
                class Person{
                public:
                    int age;
                    
                    // 拷贝构造
                    Person(const Person & p){
                        age = p.age;
                        cout << "Person拷贝构造调用" << endl;
                    }
                }
                ```
                - 调用方法
                    - 括号法
                        ```c
                        // 括号法
                        Person p3(p2);
                        ```
                    - 显示法
                        ```c
                        // 显示法
                        Person p3 = Person(p2);
                        
                        // Person(p2)也是匿名对象
                        // 但不要利用拷贝构造函数初始化匿名对象
                        Person(P2); // 单独这么写会被误认为声明，不可以这么写
                        ```
                    - 隐式转换法
                        ```c
                        Person p5 = p2; // 等价于Person p5 = Person(p2);
                        ```
                - 调用时机
                    - 使用一个已创建完毕对象初始化新的对象
                        ```c
                        Person p2(p1);
                        ```
                    - 值传递
                        ```c
                        //相当于Person p1 = p;
                        void doWork(Person p1) {}
                        void test02() {
                        	Person p; //无参构造函数
                        	doWork(p);
                        }
                        ```
                    - 值方式返回局部对象
                        ```c
                        Person doWork2()
                        {
                        	Person p1;
                        	cout << (int *)&p1 << endl;
                        	return p1;
                        }
                        
                        void test03()
                        {
                        	Person p = doWork2();
                        	cout << (int *)&p << endl;
                        }
                        
                        
                        int main() {
                        
                        	//test01();
                        	//test02();
                        	test03();
                        
                        	system("pause");
                        
                        	return 0;
                        }
                        ```
        - [ ] 构造函数调用规则
        
            默认情况下一个类有的函数
            - 默认构造函数(无参构造函数，函数体为空)
            - 默认析构函数(无参析构函数，函数体为空)
            - 默认拷贝构造函数(对属性进行值拷贝)
        - [ ] 注意事项<br>
            - 如果用户定义有参构造，c++不提供默认无参构造，但提供默认拷贝构造
            - 如果用户定义拷贝构造，c++不会提供其他构造函数
        - [ ] 深浅拷贝
            - 浅拷贝：简单赋值拷贝操作
                - 问题：会将堆区内存重复释放
                    ```c
                    // 定义类
                    class Person{
                     public:
                        int * m_Height = new int (10);
                    
                    // 析构代码将堆区开辟数据释放
                    ~Person(){
                        if(m_Height != NULL){
                            delete m_Height;
                            m_Height = NULL;
                        }
                        cout << "Person析构函数调用" << endl;
                     }
                    };
                    
                    
                    // 调用
                    void test(){
                        Person p1;
                        Person p2(p1);
                    }
                    
                    int main(){
                        test(); // 会报错
                        //因为是浅拷贝，p2内容与p1内容指向内存一致，
                        //析构时先进后出，先释放p2，此时p1相应内存也被释放，
                        //所以再次释放会报错
                        
                        system("pause");
                        return 0;
                    }
                    ```
            - 深拷贝：在堆区重新申请空间进行拷贝操作
                ```c
                // 定义类
                    class Person{
                     public:
                        int * m_Height = new int (10);
                        
                    // 深拷贝
                    Person(const Person & p){
                        m_Height = new int (*p.m_Height);
                    }
                    
                    // 析构代码将堆区开辟数据释放
                    ~Person(){
                        if(m_Height != NULL){
                            delete m_Height;
                            m_Height = NULL;
                        }
                        cout << "Person析构函数调用" << endl;
                     }
                    };
                    
                    
                    // 调用
                    void test(){
                        Person p1;
                        Person p2(p1);
                    }
                    
                    int main(){
                        test(); 
                        // 深拷贝，另开辟空间，不会出现析构时指向同一内存
                        
                        system("pause");
                        return 0;
                    }
                
                ```
        - [ ] 初始化列表<br>
            初始化属性
            ```c
            // 语法：构造函数():属性1(值1),属性2(值2),...{}
            class Person{
            public:
                int m_A;
                int m_B;
                int m_C;
                // 第一种写法
                Person():m_A(10),m_B(10),m_C(10){
                    
                }
                
                // 第二种写法
                Person(int a,int b,int c):m_A(a),m_B(b),m_C(c){
                    
                }
            };
            ```
                    
    - 析构函数
    
        对象销毁前系统自动调用，执行一些清理工作
        - [ ] 语法
            ```
            ~类名(){}
            ```
        - [ ] 特点
            - 没返回值也不写void
            - 函数名与类名相同，前加~
            - 不可有参数，不可重载
            - 在对象销毁前自动调用，无需手动调用
                ```c
                class Person{
                public:
                    // 析构函数
                    ~Person(){
                        cout << "Person析构函数调用" << endl;
                    }
                };
                ```
2. 类对象作为类成员
    ```c
    class A{};
    class B{
    public:
        A a;
    };
    ```
    调用时先构造A，再构造B；析构时先析构B，再析构A，顺序相反
3. 静态成员
    - 静态成员变量
        - [ ] 所有对象共享同一份数据
        - [ ] 在编译阶段分配内存
        - [ ] 类内声明，类外初始化
        ```c
        // 定义
        class Person{
        public:
            static int m_A;
        private:
            static int m_B;
        };
        int Person::m_A = 10;
        int Person::m_B = 10;
        // 必须有初始化
        
        // 调用,访问
        // 通过对象访问
        Person p1;
        Person p2;
        p1.m_A = 100; // p1,p2的m_A都变为100,因为指向同一份数据
        
        // 通过类名访问
        Person::m_A;
        
        ```
    - 静态成员函数
        - [ ] 所有对象共享一个函数
        - [ ] 静态成员函数只能访问静态成员变量
        ```c
        // 定义
        class Person{
        public:
            static void func(){
                m_A = 100;
            }
            
            static int m_A;
        };
        int Person::m_A = 0;
        
        // 调用
        Person p1;
        p1.func();
        
        Person::func();
        ```
4. c++对象模型和指针
    - 成员变量和成员函数分开存储
        - [ ] 只有非静态成员变量才属于类对象上
        - [ ] 空类占用空间为1字节 --> c++编译器为空对象分配空间，为区分占内存位置
    - this指针
        - 特点
            - [ ] this指针指向被调用成员函数所属对象
            - [ ] this指针是一个隐含每一个非静态成员函数内的一种指针
            - [ ] this指针不需要定义，直接用即可```this->age;```
        - 用途
            - [ ] 当形参和成员变量重名，可用this区分
            - [ ] 当类非静态成员函数返回对象本身，可使用```return *this;```
        -  例子<br>
            this指针指向被调用成员函数所属对象
            ```c
            // 定义
            class Person{
            public:
                int age;
                Person(int a){
                    age = a;
                }
                
                // 返回类型若为值则会复制一个新的对象，相当于值传递，所以用引用可以链式传递
                Person & PersonAddAge(Person &p){
                    this->age += P.age;
                    return *this;
                }
            };
            
            // 调用
            Person p1(10);
            Person p2(20);
            p2.PersonAddAge(p1).PersonAddAge(p1);
            ```
    - 空指针访问成员函数
        ```c
        // 定义
        class Person{
        public:
            int age = 10;
            void T1(){
                cout << "调用T1" << endl;
            }
            void T2(){
                cout << age << "调用T2" << endl;
             }
        };
        
        // 调用
        Person *p1 = NULL;
        p1->T1(); //正确
        p2->T2(); // 运行失败，因为空指针调用，函数包含了类成员age
        
        ```
    - const 修饰成员函数<br>
        成员函数后加const --> 常函数
        - [ ] 不可修改成员属性
        - [ ] 成员属性声明时关键字mutable后，常函数中仍可修改
        ```c
        class Person{
        public:
        
            // 相当于 const Person *const this; 值和指向都改不了
            void showPerson() const
            {
                
            }
        };
        
        // 若const成员函数里有如下
        mutable int m_B; // 该属性可更改
        
        const Person p; // 常对象
        ```
#### 友元
1. 目的：<br>
    让一个函数或类可访问另一个类中的私有成员，使用关键字friend
2. 全局函数作友元
    ```c
    class Building{
        friend void goodGay(Building *b);
    public:
        Building(){
            m = "你好";
        }
    private:
        string ml
    };
    
    void goodGay(Building *b){
        cout << b->m << endl;
    }
    
    // 类内加入friend void goodGay(Building *b);
    // 就可以访问私有成员
    ```
3. 类作友元
    ```c
    class Building{
        friend class GoodGay; //GoodGay 可访问该类的私有成员
        ...
    };
    ```
4. 成员函数作友元
    ```c
    class Building{
        friend void GoodGay::visit(); // GoodGay的visit函数可访问该类私有成员
    };
    ```
#### 运算符重载
1. 加号重载
    - 成员函数重载+号
        ```c
        class Person{
         public:
            int mA;
            int mB;
            Person operator+(Person &p){
                Person temp;
                temp.mA = this->mA + p.mA;
                temp.mB = this->mB + p.mB;
                return temp;
            }
        };
        ```
    - 全局函数重载+号
        ```c
        Person operator+(Person &p1, Person &p2){
            Person temp;
            temp.mA = p1.mA + p2.mA;
            temp.mB = p1.mB + p.2mB;
            return temp;
        }
        ```
    都可采用如下调用
    ```c
    Person p1;
    p1.mA = 10;
    p1.mB = 10;
    Person p2;
    p2.mA = 20;
    p2.mB = 20;
    Person p3 = p1 + p2;
    ```
    - 运算符重载也可发生函数重载
        ```c
        Person operator+(Person &p1, int num){
            Person temp;
            temp.mA = p1.mA + num;
            temp.mB = p1.mB + num;
            return temp;
        }
        
        ```
2. 左移运算符重载<br>
    以成员函数无法实现cout << p;
    ```c
    // 只能用全局函数
    ostream & operator<<(ostream & cout, Person &p){
        cout << "mA = " << p.mA << " mB = " << p.mB;
        rerurn cout;
    }
    ```
3. 递增运算符重载
    ```c
    class MyInteger{
        friend  ostream & operator<<(ostream & cout, MyInteger &p);
    public:
        MyInteger(){
            m_Num = 0;
        }
        
        // 前置递增
        MyInteger& operator++(){
            m_Num++;
            return *this;
        }
        
        // 后置递增,用占位符
        MyInteger operator++(int){
            MyInteger temp = *this;
            m_Num++;
            return temp;
        }
        
    private:
        int m_Num;
    };
    
    ostream & operator<<(ostream & cout,  MyInteger &p){
        cout << p.m_Num;
        rerurn cout;
    }
    ```
4. 赋值运算符<br>
    默认运算符operator++是浅拷贝
    ```c
    // 重载深拷贝
    // 定义
    class Person{
    public:
        int *m_Age;
        Person(int age){
            m_Age = new int(age);
        }
        
        // 重载=
        Person& operator=(Person &p){
            if (m_Age != NULL){
                delete m_Age;
                m_Age = NULL;
            }
            m_Age = new int(*p.m_Age);
            return *this;
        }
        
        // 析构函数
        ~Person(){
          if (m_Age != NULL){
                delete m_Age;
                m_Age = NULL;
            }  
        }
    };
    
    
    // 调用
    Person p1(18);
    Person p2(20);
    Person p3(30);
    p3 = p2 = p1;
    ```
5. 关系运算符
    ```c
    class Person{
     pubilc:
        Person(string name,int age){
            this->m_Name = name;
            this->m_Age = age;
        }
        
        bool operator==(Person &p){
            if (this->m_Name == p.m_Name) && (this->m_Age == p.m_Age){
                return true;
            }
            else
                return false
        }
        
        string m_Name;
        int m_Age;
    };
    
    
    // 调用
    Person a("章三,18);
    Person b("章三,18);
    a == b;
    ```
6. 函数调用运算符重载<br>
    重载() --> 仿函数
    ```c
    class MyAdd{
    public:
        int operator()(int num1,int num2){
            return num1 + num2;
        }
        
    };
    
    // 调用
    MyAdd myadd;
    myadd(100,100);
    
    // 或者
    MyAdd()(100,100); // 匿名函数对象
    ```
#### 继承
1. 特点<br>
    - 子类也称派生类
    - 父类也称基类
    ```c
    // 语法：class 子类:继承方式 父类{}
    class Java:public BasePage{}
    ```
2. 继承方式
    - 公共继承(:public): 除private访问不到,其余成员权限不变
    - 保护继承(:protected): 除private访问不到，其余成员权限都变为protected
    - 私有继承(:private): 除private访问不到，其余成员权限都变成private
3. 继承中对象模型
    - 父类中所有非静态成员属性都会被子类继承下去
    - 父类中私有成员属性会被编译器隐藏，访问不到，但被继承下去了
    ```c
    // 查看类布局指令
    // 打开vs下面的开发人员命令提示
    cl /d1 reportSingleClassLayout类名 文件名
    ```
4. 构造析构顺序
    ```
    先父类构造
    再子类构造
    
    先子类析构
    再父类析构
    ```
5. 继承中同名成员处理方式
    - 非静态成员
        ```c
        // 定义
        class Base{
        public:
            int A;
            int func(){}
        };
        
        class Son:public Base{
        public:
            int A;
            int func(){}
        };
        
        // 调用
        // 调用子类成员
        Son S;
        S.A;
        S.func();
        // 调用父类成员
        S.Base::A;
        S.Base::func();
        ```
        - __注意__：<br>
            - [ ] 若子类中出现与父类同名函数，子类同名成员会隐藏所有父类同名成员函数
            - [ ] 若Base中有func()和func(int a),Son中只有func(),```s.func(10);```会报错,应该为```s.Base::func(10)```
    - 静态成员<br>
        与非静态成员处理方式一样
        ```c
        // 假设mA为静态成员
        // 访问子类成员
        Son s;
        s.mA;
        Son::mA;
        
        // 访问父类成员
        s.Base::mA;
        Son::Base::mA;
        ```
6. 多继承<br>
    一个儿子多个爸爸，可能引发父类中有同名成员需加作用域区分
    ```c
    // 语法：class 子类:继承方式 父类1,继承方式 父类2...{}
    class Son:public F1,public F2,protected F3{}
    ```
7. 菱形继承
    - 概念
        - [ ] 两个派生类继承同一个基类
        - [ ] 又有某个类同时继承两个派生类
    - 存在问题<br>
        两个父类有同名成员需加作用域区分
    - 解决方法
        - 利用虚继承，继承之前加关键字virtual,类变为虚基类
        - 虚继承继承的是指针，指向都是同一内存空间
        - 有一个类不管父类子类值改变，父类子类相应成员都改变
        ```c
        // 定义
        class Animal{
        public:
            int Age;
        };
        
        class Sheep:virtual public Animal{};
        class Tuo:virtual public Animal{};
        class SheepTuo:public Sheep,public Tuo{};
        
        // 定义
        SheepTuo st;
        st.Age = 10;
        //st.Sheep::Age, st.Tuo::Age , 
        // st.Sheep::Animal::Age, st.Tuo::Animal::Age 
        // 以上的值都变为10
        ```
#### 多态
1. 静态多态：函数重载，运算符重载<br>

    特点：函数地址在编译阶段就确定
    ```c
    // 定义
    class Animal{
    public:
        void speak(){
            cout << "动物" << endl;
        }
    };
    
    class Cat:public Animal{
    public:
        void speak(){
            cout << "小猫" << endl;
        }
    };
    
    void doSpeak(Animal &animal){
        animal.speak();
    }
    
    // 调用
    int main(){
        Cat cat;
        doSpeak(cat);
        // 输出为动物
        // 因为函数地址在编译时就已确定
        // doSpeak在编译时就指向的是Animal类
    }
    ```
2. 动态多态:派生类和虚函数实现运行多态<br>
 
    动态多态在运行阶段才确定函数地址
    ```c
    // 定义
    class Animal{
    public:
        void speak(){
            cout << "动物" << endl;
        }
    };
    
    class Cat:public Animal{
    public:
        virtual void speak(){
            cout << "小猫" << endl;
        }
    };
    
    void doSpeak(Animal &animal){
        animal.speak();
    }
    
    // 调用
    int main(){
        Cat cat;
        doSpeak(cat);
        // 输出为小猫
        // 因为函数地址在运行时才确定
        // doSpeak在运行时就指向的是Cat类
    }
    ```
    - 满足条件
        - [ ] 有继承关系
        - [ ] 子类重写父类虚函数（重写：函数返回类型，函数名，函数列表完全相同）
    - 虚函数实质<br>
        虚函数的类和子类会多4个字节，是用来记录函数地址
    - 优点
        - [ ] 代码组织结构清晰
        - [ ] 可读性强
        - [ ] 利用前期和后期扩展以及维护
        - [ ] __真实开发中开闭原则__ --> 对扩展进行开放，对修改进行关闭
    ```c
    // 实现计算器
    // 定义
    class AbstractCalculator{
    public:
        virtual int getResult(){
            return 0;
        }
        int Num1;
        int Num2;
    };
    
    // 加法计算器
    class AddCalculator:public AbstractCalculator{
    public:
        int getResult(){
            return Num1 + Num2;
        }
    };
    
    // 调用
    AbstractCalculator *abs = new AddCalculator;
    abs->Num1 = 10;
    abs->Num2 = 10;
    abs->getResult();
    delete abs;
    ```
    - 纯虚函数抽象类<br>
        上述虚函数有无定义其实都可
        - [ ] 特点
            - 类有纯虚函数，类称为抽象类
            - 无法实例化对象
            - 子类必须重写抽象类中春虚函数，否则也为抽象类
        - [ ] 语法
            ```c
            virtual 返回值类型 函数名(参数列表) = 0;
            ```
    - 虚析构和纯虚析构
        - [ ] 解决的问题<br>
            多态使用时，若子类有属性开辟到堆区，父类指针在释放时无法调用到子类析构代码
            ```c
            // 定义
            class Animal{};
            class Cat:public Animal{
            public:
                Cat(string name)
            	{
            		cout << "Cat构造函数调用！" << endl;
            		m_Name = new string(name);
            	}
            	virtual void Speak()
            	{
            		cout << *m_Name <<  "小猫在说话!" << endl;
            	}
            	~Cat()
            	{
            		cout << "Cat析构函数调用!" << endl;
            		if (this->m_Name != NULL) {
            			delete m_Name;
            			m_Name = NULL;
            		}
            	}
            
            public:
            	string *m_Name;
            };
            
            // 调用
            Animal *animal = new Cat("Cat");
            animal->speak;
            delete animal;
            // 父类指针在析构不会调用子类析构，导致子类有堆栈，可能会导致内存泄漏
            
            ```
        - [ ] 解决方法<br>
            将父类中析构函数改为虚析构或纯虚析构
        - [ ] 二者共性
            - 可解决父类指针释放子类对象问题
            - 需有具体函数实现
        - [ ] 二者不同<br>
            纯虚析构属于抽象类无法实例化对象
        ```c
        // 虚析构函数
        class Animal{
            virtual ~Animal(){
                cout << "Animal虚析构函数" << endl; 
            }
        };
        class Cat:public Animal{
        public:
            Cat(string name)
        	{
        		cout << "Cat构造函数调用！" << endl;
        		m_Name = new string(name);
        	}
        	virtual void Speak()
        	{
        		cout << *m_Name <<  "小猫在说话!" << endl;
        	}
        	~Cat()
        	{
        		cout << "Cat析构函数调用!" << endl;
        		if (this->m_Name != NULL) {
        			delete m_Name;
        			m_Name = NULL;
        		}
        	}
        
        public:
        	string *m_Name;
        };
            
        // 纯虚析构
        class Animal{
            virtual ~Animal() = 0;
        };
        Animal::~Animal(){
            cout << "Animal纯虚构函数调用" << endl;
        }
        class Cat:public Animal{
        public:
            Cat(string name)
        	{
        		cout << "Cat构造函数调用！" << endl;
        		m_Name = new string(name);
        	}
        	virtual void Speak()
        	{
        		cout << *m_Name <<  "小猫在说话!" << endl;
        	}
        	~Cat()
        	{
        		cout << "Cat析构函数调用!" << endl;
        		if (this->m_Name != NULL) {
        			delete m_Name;
        			m_Name = NULL;
        		}
        	}
        
        public:
        	string *m_Name;
        };
        
        ```
#### 文件操作
1. 一些必备
    - 头文件```#include<fstream>```
    - 文件操作类型
        - [ ] ofstream --> 写操作
        - [ ] ifstream --> 读操作
        - [ ] fstream --> 读写操作
    - 文件打开方式
        |代码实现|表示含义 |
        |:-:|:-:|
        | ios::in| 为读文件打开|
        | ios::out| 为写文件打开|
        | ios::ate| 初始位置:文件尾|
        | ios::app| 追加方式写文件|
        | ios::trunc| 如果文件存在先删除再创立|
        | ios::binary| 二进制方式|
2. 文本文件
    - 写操作
        ```c
        #include<fstream>
        ofstream ofs;
        ofs.open("test.txt",ios::out);
        ofs << "姓名：张三" << endl;
        ofs.close();
        ```
    - 读操作
        ```c
        #include<fstream>
        ifstream ifs;
        ifs.open("test.txt",ios::in);
        // 判断文件是否打开成功
        if (!ifs.is_open()){
            cout << "文件打开失败" << endl;
            return;
        }
        
        // 第一种读数据方法
        char buf[1024] = {0};
        while (ifs >> buf){
            cout << buf << endl;
        }
        
        // 第二种读取方法
        char buf[1024] = {0};
        while (ifs.getline(buf,sizeof(buf)){
            cout << buf << endl;
        }
        
        // 第三种读取方法
        string buf;
        while (getline(ifs,buf){
            cout << buf << endl;
        }
        
        // 第四种读取方法
        char c;
        while (c=ifs.get()!=EOF){
            cout << c;
        }
        
        // 关闭文件
        ifs.close();
        
        //---------------------
        // 判断文件是否为空
        char ch;
        ifs >> ch;
        if (ifs.eof()) 
            cout << "文件为空文件" << endl;
        ifs.close();
        ```
3. 二进制文件<br>
    可把结构写入文件
    ```c
    // 定义一个结构
    #include <fstream>
    #include <string>
    
    class Person
    {
    public:
    	char m_Name[64];
    	int m_Age;
    };
    ```
    - 写文件
        ```c
        #include <fstream>
        #include <string>
        ofstream ofs("person.txt", ios::out | ios::binary);
	    
	    // 或者可采用以下打开方式
	    // ofstream ofs;
    	//ofs.open("person.txt", ios::out | ios::binary);
    
    	Person p = {"张三"  , 18};
    
    	ofs.write((const char *)&p, sizeof(p));
    
    	ofs.close();
        ```
    - 读文件
        ```c
        #include <fstream>
        #include <string>
        ifstream ifs("person.txt", ios::in | ios::binary);
    	if (!ifs.is_open())
    	{
    		cout << "文件打开失败" << endl;
    	}
    
    	Person p;
    	ifs.read((char *)&p, sizeof(p));
    
    	cout << "姓名： " << p.m_Name << " 年龄： " << p.m_Age << endl;
        ```

        