#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int a_new,b_new,a_inv;
 int n,a,b;

void find_Decryption_Key(int a,int b,int n)
{
   int i=1;
	if(a<0)
	{
		while(a<0)
		{
			a=a+n;
		}
	}
	if(b<0)
	{
		while(b<0)
		{
			b=b+n;
		}
	}

	while((a*i)%n!=1)
	{
        i++;
	}
	
	a_new=a_inv=i;
	b_new=-(a_inv*b)%n;
	// printf("%d\n",a_dash);
	// printf("%d\n",b_dash);
}


char* encrypted(char initial[],int length,int a,int b,int n)
{
   //char encrypted_Array[length];
   int j;//int a=-3; int b=2;
   char *encrypted_Array;
   encrypted_Array=malloc (sizeof (char) * length);
   int t=length/n;
   for(int k=0;k<t;k++)
   {
   	int i=0;
   	while(i<n)
   	{
   		int temp=a*i+b;

   		if(temp<0)
   		{
   			while(temp<0)
   			{
   				temp=temp+n; 
   			}
   		}
   		j=temp%n;
   		//j=(a*i+b)%n;
        encrypted_Array[k*n+i]=initial[j+k*n];

        i++;
   	}
   }

   for(int i=0;i<length;i++)
   {
      char m=encrypted_Array[i];
      if(m=='\0')
      {
      	printf("\\0");
      }
      else
      {
      	printf("%c",m);
      }
   }
    printf("\n");
    return encrypted_Array;
}

char* decrypted(char *input,int length,int a,int b,int n)
{
  char *decrypted_Array;//int a=3; int b=-1;
  int j;
   decrypted_Array=malloc (sizeof (char) * length);
   int t=length/n;
   for(int k=0;k<t;k++)
   {
   	int i=0;;
   	while(i<n)
   	{
   		int temp=a*i+b;

   		if(temp<0)
   		{
   			while(temp<0)
   			{
   				temp=temp+n; 
   			}
   		}
   		j=temp%n;

        decrypted_Array[k*n+i]=input[j+k*n];

        i++;
   	}
   }

   for(int i=0;i<length;i++)
   {
      char m=decrypted_Array[i];
      printf("%c",m);
      
   }
    printf("\n");
    
   return decrypted_Array;
}




int main()
{
     size_t size = 0;
     FILE *fp = fopen("inputfile.txt", "r");
     fseek(fp, 0, SEEK_END);
     size = ftell(fp); 
     rewind(fp);
      char string[size+1];
      fread(string, size, 1, fp); 
      string[size]='\0';
	   fclose(fp);
   
	//char str[]="Rutuja Bhagwan Kendre";
	int length_2=strlen(string);
	printf("%d\n",length_2);

	 int new_Length=length_2;
     printf("Enter the value of n : ");
	 scanf("%d",&n);
	 printf("Value of n :%d\n",n);
	 printf("Enter the value of a : ");
	 scanf("%d",&a);
	 printf("Value of n :%d\n",n);
	 printf("Enter the value of b : ");
	 scanf("%d",&b);
	 printf("Value of n :%d\n",n);
     find_Decryption_Key(a,b,n);


	if(length_2%n!=0)
	{
		int quotient=length_2/n;
		new_Length=n*(quotient+1);
	}
    
	char arr[new_Length];
	for(int i=0;i<length_2;i++)
	{
		arr[i]=string[i];
	}
	for(int k=length_2;k<new_Length;k++)
	{
       arr[k]='\0';
	}

	
	char *output=encrypted(arr,new_Length,a,b,n);
  int encrypted_length=strlen(output);
  printf("%d",encrypted_length);
  
	decrypted(output,new_Length,a_new,b_new,n);

   FILE *file = fopen("output.txt", "w" );

   int results = fputs(output, file);
   if (results == EOF) 
   {
     printf("Failed to write in file");
   }
   fclose(file);

	return 0;
}