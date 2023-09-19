# interview  

q1_Q2:  
由於char變數儲存ASCII裡的一個整數編號，且binary search需用在排序好的數列，故"111"(ascii:49)應該放在"aa"(ascii:97)前面。

q2:  
此程式的問題有兩個  
1.鎖應用不當導致死鎖，同時使用counter_mtx及rwlock兩個鎖，由於thd_func1與thd_func2兩者使用鎖的順序相反，有可能導致thd_func1鎖上counter_mtx同時thd_func2鎖上rwlock，由於兩者若要繼續運行皆需要對方鎖上的資源，最終導致死鎖。  
2.thd_func1使用讀鎖卻改動了共用資料，雖然thd_func2使用寫鎖而不受影響，若同時有其他執行緒使用讀鎖而無任何寫鎖等待，則會導致讀取未預期的資料。  

解決步驟1: thd_func1或thd_func2調換上鎖與解鎖的先後順序

void * thd_func1 (void *arg) {  
&emsp;&emsp;pthread_rwlock_rdlock(&rwlock);  
&emsp;&emsp;counter_mtx.lock();  
&emsp;&emsp;counter++;  
&emsp;&emsp;counter_mtx.unlock();  
&emsp;&emsp;pthread_rwlock_unlock(&rwlock);  
&emsp;&emsp;return NULL;  
}  
或者修改  
void *thd_func2 (void *arg) {  
&emsp;&emsp;counter_mtx.lock();  
&emsp;&emsp;pthread_rwlock_wrlock(&rwlock);  
&emsp;&emsp;counter--;  
&emsp;&emsp;pthread_rwlock_unlock(&rwlock);  
&emsp;&emsp;counter_mtx.unlock();  
&emsp;&emsp;return NULL;  
}  

解決步驟2: pthread_rwlock_rdlock(&rwlock); => pthread_rwlock_wrlock(&rwlock);   
解決步驟3: 由於修改後等同只用一個鎖，故可將任意一個鎖刪除。  

