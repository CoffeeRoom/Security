
#include <stdio.h>

int p,q,n,t,flag;
int e[100], d[100], temp[100];

int i,j;

char msg[100];

void setPossibleEDValue();
void encryptMsg();
void decryptMsg();
void printMsg();

int main(int argc, const char * argv[]) {
    
    int m[100];
    
    // set prime number 'p' & 'q'
    p = 7;
    q = 17;
    
    n = p * q;
    t = (p-1) * (q-1);
    
    setPossibleEDValue();
    
    // set message to encrypt
    snprintf(msg, sizeof(msg), "hello, world!");
    
    // copy character array to integer array
    for (i = 0; i < sizeof(msg); i++) {
        m[i] = msg[i];
    }
    
    // Message Encryption
    encryptMsg(&m, 13); // original msg has 13 characters
    
    printf("\nEncrypted Message is: \n");
    printMsg(&m);
    
    // Message Decryption
    decryptMsg(&m);
    
    printf("\nDecrypted Message is: \n");
    printMsg(&m);
    
    return 0;
    
}

int isPrime(long int pr) {
    int i;
    j=sqrt(pr);
    for(i=2;i<=j;i++)
    {
        if(pr%i==0)
            return 0;
    }
    return 1; 
}

long int cd(long int x) {
    long int k=1;
    
    while(1) {
        k=k+t;
        if(k%x==0) return(k/x);
    } 
}

void setPossibleEDValue(){

    int k = 0;

    // find possible e & d values
    for(i=2;i<t;i++) {
        
        if(t%i==0) continue;
        
        flag = isPrime(i);
        
        if(flag==1&&i!=p&&i!=q) {
            
            e[k]=i;
            flag = cd(e[k]);
            
            if(flag>0) {
                d[k]=flag;
                k++;
            } 
            if(k==99) break;
        }
    }
    // print possible e & d values
    printf("Possible e & d values are: ");

    for(i=0;i<j-1;i++)
        printf("\n%2d\t%d",e[i],d[i]);
    printf("\n");
}

void encryptMsg(int *m, int len) {
    
    long int pt,ct,key=e[0],k;
    i=0;
    
    while(i != len) {
        
        pt=m[i];
        pt=pt-96;
        k=1;
        
        for(j=0;j<key;j++) {
            k=k*pt;
            k=k%n;
        }
        
        temp[i]=k;
        ct=k+96;
        m[i]=ct;
        i++;
        
    }
    
    m[i]=-1;

}

void decryptMsg(int* m) {
    
    long int pt,ct,key=d[0],k;
    i=0;
    
    while(m[i]!=-1){
        ct=temp[i];
        k=1;
        for(j=0;j<key;j++) {
            
            k=k*ct;
            k=k%n;
        }
        pt=k+96; 
        m[i]=pt; 
        i++; 
    } 
    m[i]=-1;
}

void printMsg(int* m) {
    for(i=0;m[i]!=-1;i++)
        printf("%c",m[i]);
    printf("\n");
}




