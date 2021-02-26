#include  <iostream>
#include <fstream>
using namespace std;

class listNode {
	public:
		int data;
		listNode *next;//the next pointer
		
	listNode(int d){//assigns data to node upon initialization
		data = d;
	}	

	void printNode(listNode *node, ofstream &outFile){
	    if (this->next == NULL)
	        outFile << "(" << this->data <<", NULL)-->NULL";
	    if (this->next != NULL)
	        outFile << "(" << this->data <<","
	        << this->next->data << ")-->" ;
	}
};

class LLStack{
	public:
	int length = 0;
	
	listNode *top;//node pointer to the top
	
	LLStack(){
		top = new listNode(-9999);//creates the first value
		top->next = NULL;//points to the next empty value
	}
	
	void push(listNode *dNode) {
		dNode->next = top->next;
		top->next = dNode;
        length++;
    }
    listNode* pop(){
    	listNode *temp = new listNode(-9999);
    	temp = top->next;
    	if(isEmpty()){
    		return NULL;
		}
		else{
			top->next = top->next->next;
			length--;
		}
		return temp;
	}
	bool isEmpty(){
		if (length == 0) return true;
		return false;
	} 
	void printStack(ofstream &outFile, LLStack stack){
	    listNode *tmp;
	    tmp = stack.pop();
	    outFile<<"Top-->("<<top->data<<","<<tmp->data<<")-->";
	    while (tmp->next != NULL){
		    outFile << "("<<tmp->data << "," 
	    	    << tmp->next->data <<")-->";
	        tmp = stack.pop();
	    }
		outFile << "("<<tmp->data << "," << "NULL)-->NULL";
	}
	void buildStack (ifstream &inFile, ofstream &outFile1){
		char op;
	    int data;
	    listNode* junk;
	    LLStack S;
	    while (inFile >> op >> data){
	    	if (op == '+'){
	    	    S.push(new listNode(data));
	    	}
		    if (op == '-'){
		        junk = S.pop();
		        if (junk != NULL)
		            free(junk);
		        else
		            outFile1 << "Stack is empty";
		    }  
	    }
	    printStack(outFile1,S);
	}
};

class LLQueue{
	public:
	int length = 0;
	
	listNode *head,*tail;
	
	LLQueue(){
	    listNode* dummy = new listNode(-9999);
	    dummy->next = NULL;
		head = dummy;
		tail = dummy;
	}
	

	void insertQ(listNode *dNode) {
        listNode *tmp=head;
        if(tmp==NULL){
            return;
        }
        tmp=dNode;
        tmp->next=NULL;
        if(head==NULL)
            head=tail=tmp;
        else{
            tail->next=tmp;
            tail=tmp;
        }
    length++;
    }
    
    listNode* deleteQ(){
		if (head->next != NULL){
			head = head->next;
		}
        else
            return NULL;
        //cout<<head->data<<" ";
		return head;
		
	}
    bool isEmpty(){
		if (length == 0) return true;
		return false;
	}
	void printQ(ofstream &outFile, LLQueue queue){
	    listNode *tmp;
        tmp = queue.deleteQ();
        outFile<<"Top-->("<<head->data<<","<<tmp->data<<")-->";
	    while (tmp->next != NULL){
		    outFile << "("<<tmp->data << "," 
	    	    << tmp->next->data <<")-->";
	        tmp = queue.deleteQ();
	    }
		outFile << "("<<tmp->data << "," << "NULL)-->NULL";
	}
	void buildQueue (ifstream &inFile, ofstream &outFile2){
		char op;
	    int data;
	    listNode* junk;
	    LLQueue Q;
	    while (inFile >> op >> data){
	    	if (op == '+'){
	    	    Q.insertQ(new listNode(data));
	    	}
		    if (op == '-'){
		        junk =  
				Q.deleteQ();
		        if (junk != NULL)
		            free(junk);
		        else
		            outFile2 << "Stack is empty";
		    }
	    }
	    printQ(outFile2,Q);
	}
};

class LLlist{
	public:
	int length = 0;
	
	listNode *head;
	
	LLlist(){
		head = new listNode(-9999);
	}
	
	
	void listInsert(listNode *dNode) {
	    listNode *tmp = head;
	    
        while (tmp->next != NULL){
	    	if (tmp->data < dNode->data)
	            tmp = head->next;
	        if (tmp->data == dNode->data)
	            tmp = tmp->next;
	        else{
	            listNode *tmp2;
	            tmp2->data = dNode->data;
	            tmp2->next = tmp->next;
	            tmp->next = tmp2;
        }    
        length++;
    	}    
    }
	listNode* deleteOneNode(int val){
		listNode* tmp = head;
		for (int i=0; i<length; i++){
		    tmp = tmp->next;
			if (tmp->next->data==val) {
			    tmp->next = tmp->next->next;
			    length--;
			    return tmp;	    
			}
		
		}
		return NULL;
	}
	void printList(ofstream &outFile3){
	    outFile3<<"Head-->";
	    listNode *tmp = head;
	    while (tmp != NULL){
	        tmp->printNode(tmp, outFile3);
	       tmp = tmp->next;
	    }
	}
	void buildList (ifstream &inFile, ofstream &outFile3){
		char op;
	    int data;
	    listNode* junk;
	    LLlist listHead;
	    
	    while (inFile >> op >> data){
	    	if (op == '+'){
	    	    listHead.listInsert(new listNode(data));
	    	}
		    /*if (op == '-'){
		        junk = listHead.deleteOneNode(data);
		        if (junk != NULL)
		            free(junk);
		        else
		            outFile3 << "List is empty"; 
		    }*/
	    }
	    printList(outFile3);
	}
};

int main (int argc, char *argv[]){	
	ifstream input;
	input.open(argv[1]);
	ofstream output1, output2, output3;
	output1.open(argv[2]);
	output2.open(argv[3]);
	output3.open(argv[4]);
	
	ifstream inFile;
	inFile.open(argv[1]);
	ofstream outFile1, outFile2, outFile3;

	
	LLStack myStack;
	myStack.buildStack(input, output1);
	input.close();
	
	input.open(argv[1]);
	LLQueue myQueue;
	myQueue.buildQueue(input, output2);
	input.close();
	
	input.open(argv[1]);
    LLlist myList;
	myList.buildList(input, output3);
	input.close();
	
	output1.close();
	output2.close();
	output3.close();
	cout<<"Done";
	return 0;
}

