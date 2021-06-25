#include<iostream>
#include<unordered_map>
#include<list>
#include<string>
using namespace std;

class Node{
    public:
        string key;
        int val;
        Node(string k , int v){
            this->key = k;
            this->val = v;
        }
};

class LRU_cache{
    private:
        int maxsize;
        list<Node> l ;
        unordered_map< string , list<Node>::iterator > mp;

    public:

        void insert(string key , int val){
            
            auto f = mp.find(key);
            if(f != mp.end()){
                auto temp = mp[key];
                l.erase(temp);
                mp.erase(f);
            }
            else{

                if(l.size() == maxsize){
                    auto temp = l.back();
                    mp.erase(temp.key);
                    l.pop_back();
                }
            }

            Node n1(key,val);
            l.push_front(n1);
            mp[key] = l.begin();
        }

        int* get_val(string key){

            auto f = mp.find(key);
            if(f != mp.end()){

                int val = mp[key]->val;
                Node n1(key,val);
                l.push_front(n1);
                
                l.erase(mp[key]);
                mp.erase(f); 
                mp[key] = l.begin();

                return &(l.front().val);
            }
            return NULL;

        }

        string most_rec(){
            return l.begin()->key; 
        }

        LRU_cache(int m){
            this->maxsize =  m;
        }

};

int main(){

    LRU_cache lru(3);

    lru.insert("c" , 1);
    lru.insert("django" , 2);
    lru.insert("c++" , 3);
    lru.insert("python" , 4);

    cout<<lru.most_rec()<<endl;

    if(lru.get_val("c")){
        cout<<*lru.get_val("c")<<endl;;
    }
    else{
        cout<<"not present\n";
    }

    if(lru.get_val("python")){
        cout<<*lru.get_val("python")<<endl;
    }
    else{
        cout<<"not present\n";
    }

    cout<<lru.most_rec()<<endl;

    return 0;
}