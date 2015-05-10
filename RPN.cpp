class Solution {
public:
    /**
     * @param expression: A string array
     * @return: The Reverse Polish notation of this expression
     */
     bool isop(string hold)
     {
         if(hold=="-"||hold=="+"||hold=="/"||hold=="*"||hold=="("||hold==")")
            return true;
        else
            return false;
     }
     int get(string hold)
     {
            if(hold=="(") 
                return 0;
            else if(hold== "+" || hold=="-")
                return 1;
            else if(hold=="*"||hold=="/")
                return 2;
     }
    vector<string> convertToRPN(vector<string> &exp) {
       vector<string> ans;
       stack<string> h1;
       for(int i=0;i<exp.size();i++)
       {
           if(isop(exp[i]))
           {
               if(h1.empty() ||exp[i]=="(")
                    h1.push(exp[i]);
                else if(exp[i]==")")
                {
                    while(h1.top()!="(")
                    {
                        string c=h1.top();
                        h1.pop();
                        ans.push_back(c);
                    }
                    h1.pop();
                }
                else
                {
                    int pr = get(exp[i]);
                    while(!h1.empty() && get(h1.top())>=pr)
                    {
                        string c=h1.top();
                        h1.pop();
                        ans.push_back(c);
                    }
                    h1.push(exp[i]);
                }
           }
           else
            ans.push_back(exp[i]);
       }
       while(!h1.empty())
       {
           string c=h1.top();
                        h1.pop();
                        ans.push_back(c);
       }
       return ans;
    }
};
