#include <iostream>
#include <vector>
#include <cassert>
using namespace std;

vector<string> items_list = {"chocolate", "cream", "egg", "sugar", "fruit", "nuts", "spray", "flour", "butter", "cocoa"};
int species = 10;

vector<int> scores = {30, 120, 250, 400, 600};

vector<string> recipes_list = {"Drink","Pudding", "Parfait", "Cookie", "Cake"};
vector<vector<int>> recipes{
    vector<int>{1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
    vector<int>{1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
    vector<int>{1, 1, 0, 0, 1, 1, 1, 0, 0, 0},
    vector<int>{1, 0, 1, 1, 0, 1, 0, 1, 1, 0},
    vector<int>{1, 1, 1, 1, 1, 0, 1, 1, 0, 1}
};


int num_of_makable(vector<int> num_items, vector<int> the_recipe){
    int ret = 100000;
    for(int i=0;i<num_items.size();i++){
        if(the_recipe[i]!=0){
            ret = min(ret, num_items[i]/the_recipe[i]);
        }
    }
    return ret;
}


int greedy(vector<int> num_items){
    int ret = 0;
    assert(recipes.size()>0);
    for(int i=recipes.size()-1;i>=0;i--){
        int count = 0;
        while(num_of_makable(num_items, recipes[i])!=0){
            assert(num_items.size()==recipes[i].size());
            for(int j=0;j<num_items.size();j++){
                num_items[j] -= recipes[i][j];
                assert(num_items[j]>=0);
            }
            ret += scores[i];
            count ++;
        }
        cout<<"Make recipe "<< recipes_list[i] <<"\t x "<<count<<endl;
    }
    return ret;
}


int optimal(vector<int> num_items){
    int ret = 0;
    vector<int> optimal_step(recipes.size(),-1);
    vector<int> num_of_makable_list( recipes.size() );
    for(int i=0;i<num_of_makable_list.size();i++){
        num_of_makable_list[i] = num_of_makable(num_items, recipes[i]);
    }


    vector<int> num_of_make_the_recipe(recipes.size());
    for(num_of_make_the_recipe[1]=0; num_of_make_the_recipe[1]<=num_of_makable_list[1]; num_of_make_the_recipe[1]++){
        for(num_of_make_the_recipe[2]=0; num_of_make_the_recipe[2]<=num_of_makable_list[2]; num_of_make_the_recipe[2]++){
            for(num_of_make_the_recipe[3]=0; num_of_make_the_recipe[3]<=num_of_makable_list[3]; num_of_make_the_recipe[3]++){
                for(num_of_make_the_recipe[4]=0; num_of_make_the_recipe[4]<=num_of_makable_list[4]; num_of_make_the_recipe[4]++){

                    vector<int> need(items_list.size(),0);
                    int score_sum = 0;
                    for(int i=1;i<recipes.size();i++){
                        for(int j=0;j<need.size();j++){
                            need[j] += recipes[i][j]*num_of_make_the_recipe[i];
                        }
                        score_sum += scores[i] * num_of_make_the_recipe[i];
                    }
                    vector<int> less(species);
                    for(int i=0;i<species;i++){
                        less[i] = num_items[i] - need[i];
                    }
                    num_of_make_the_recipe[0] = max( 0, num_of_makable(less, recipes[0]) );
                    score_sum += scores[0] * num_of_make_the_recipe[0];

                    for(int i=0;i<species;i++){
                        need[i] += recipes[0][i]*num_of_make_the_recipe[0];
                    }

                    if(num_of_makable(num_items, need)>0){
                        if(ret<score_sum){
                            for(int i=0;i<recipes.size();i++){
                                optimal_step[i] = num_of_make_the_recipe[i];
                            }
                            ret = score_sum;
                        }
                    }

                }
            }
        }
    }
    for(int i=optimal_step.size()-1;i>=0;i--){
        cout<<"Make recipe "<< recipes_list[i] <<"\t x "<<optimal_step[i]<<endl;
    }

    return ret;
}

int main(){
    for(auto elm:items_list)cout<<elm<<" ";
    cout<<endl;

    vector<int> num_items(species);
    for(auto &elm: num_items)cin>>elm;

    cout<<"greedy"<<endl;
    cout<<greedy(num_items)<<endl;
    cout<<endl;
    cout<<"optimal"<<endl;
    cout<<optimal(num_items)<<endl;

}
