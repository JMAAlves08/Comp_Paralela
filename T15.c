

int vetor[n]; //vetor para armazenar quantidade de elementos maiores

/**
 * RAM
 * O(n^2)
 * PRAM
 * O(1)
*/
for(i = 0; i < n-1; i++){
  for(j = 0; j < n-i-1; j++){ 
    if(arr[i] > arr[j+1])
      vetor[i]++;//sempre que um elemento for maior, adicionar 1 a quantidade
  }
}
//apos o loop tem-se a informação: Elemento na posição X é maior que n outros elementos
//ficará na posição 0+n
int tmp[n];
/**
 * RAM
 * O(n)
 * PRAM
 * O(1)
*/
for(x=0; x<n; x++){
    tmp[vetor[x]]=arr[x]; 
}