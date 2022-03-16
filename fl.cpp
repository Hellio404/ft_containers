#include <iostream>
#include <fcntl.h>
#include <vector>
#include <unistd.h>
#define DEBUG
using namespace std;

int main()
{
    # ifdef DEBUG
        int fd = open("input.txt", O_RDONLY);
        dup2(fd, 0);    
    #endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    
        
        
    }

}