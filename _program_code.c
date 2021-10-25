#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_VALUE 255

/* TABLE
    0 1 2 3 4    Row(x)
  0 A B C D E
  1 F G H I K
  2 L M N O P
  3 Q R S T U
  4 V W X Y Z
  Col(y)
*/

struct position{
    int row;
    int column;
};

char* reverseSearchOnTable(char** table, char* sentence, struct position *pos, int table_len, int method)
{ //Find every 'translated' letter through positions
    int i, x, y, w=0, spaces=0, real_len, s_len = strlen(sentence);
    //char space_pos[32][16];
    char* new_sen = malloc(sizeof(char)*s_len);
    struct position *decr_pos;

    for(i=0; i<s_len; i++)
	{
        if(sentence[i] == ' ' || sentence[i] == 'j')
            ++spaces;
	}

    real_len = s_len - spaces; //REAL LENGTH - without spaces (not implemented yet)

    decr_pos = malloc(sizeof(struct position)*real_len);
        memcpy(decr_pos, pos, sizeof(struct position)*real_len); //make a copy of struct position array (with every word position)

    if(method == 1) //decipher
    {
        if(real_len % 2 == 0){
            for(x=0, w=0; x<(real_len/2); x++, w+=2)
			{
                decr_pos[w].row = pos[x].row;
                decr_pos[w+1].row = pos[x].column;
            }

            for(y=x, w=0; y<(x+(real_len/2)); y++, w+=2)
			{
                decr_pos[w].column = pos[y].row;
                decr_pos[w+1].column = pos[y].column;
            }

            //for(x=0; x<real_len; x++)
              //  printf("%i%i ", decr_pos[x].row, decr_pos[x].column);
        }
        else{
            for(x=0, w=0; x<(real_len/2); x++, w+=2)
			{
                decr_pos[w].row = pos[x].row;
                decr_pos[w+1].row = pos[x].column;
            }

            decr_pos[w].row = pos[x].row;
            decr_pos[0].column = pos[x].column;

            for(y=x+1, w=1; y<(x+1+(real_len/2)); y++, w+=2)
			{
                decr_pos[w].column = pos[y].row;
                decr_pos[w+1].column = pos[y].column;
            }

            //for(x=0; x<real_len; x++)
              //  printf("%i%i ", decr_pos[x].row, decr_pos[x].column);
        }

        for(x=0, w=0; x<s_len; x++,w++)
		{
            new_sen[x] = table[decr_pos[w].row][decr_pos[w].column];
        }

        new_sen[x] = '\0';

        return new_sen;
    }

    if(real_len % 2 == 0)
	{ //cipher
        for(x=0, w=0; x<(real_len/2); x++,w+=2){
            /*for(i=0; i<spaces; i++){
                if(atoi(space_pos[i]) == x){
                    new_sen[x] = ' ';
                    ++x;
                }
            }*/
            new_sen[x] = table[decr_pos[w].row][decr_pos[w+1].row];
            //printf("%i%i ", decr_pos[w].row, decr_pos[w+1].row);
        }

        for(y=x, w=0; y<(x+(real_len/2)); y++, w+=2){
            /*for(i=0; i<spaces; i++){
                if(atoi(space_pos[i]) == y){
                    new_sen[y] = ' ';
                    ++y;
                }
            }*/
            new_sen[y] = table[decr_pos[w].column][decr_pos[w+1].column];
            //printf("%i%i ", decr_pos[w].column, decr_pos[w+1].column);
        }
    }
    else
    {
        for(x=0, w=0; x<(real_len/2); x++,w+=2)
		{
            /*for(i=0; i<spaces; i++){
                if(atoi(space_pos[i]) == x){
                    new_sen[x] = ' ';
                    ++x;
                }
            }*/
            new_sen[x] = table[decr_pos[w].row][decr_pos[w+1].row];
            //printf("%i%i ", decr_pos[w].row, decr_pos[w+1].row);
        }

        new_sen[x] = table[decr_pos[w].row][decr_pos[0].column];
        //printf("%i%i ", decr_pos[w].row, decr_pos[0].column);


        for(y=x+1, w=1; y<(x+1+(real_len/2)); y++, w+=2){
            /*for(i=0; i<spaces; i++){
                if(atoi(space_pos[i]) == y){
                    new_sen[y] = ' ';
                    ++y;
                }
            }*/
            new_sen[y] = table[decr_pos[w].column][decr_pos[w+1].column];
            //printf("%i%i ", decr_pos[w].column, decr_pos[w+1].column);
        }
    }

    new_sen[y] = '\0'; //add terminator at the end of the sentence (to avoid memory problems)

    return new_sen;
}

struct position *searchOnTable(char** table, char* sentence, int table_len)
{ //Search on the table every letters
    struct position * pos;
    int i, x, y, w=0, spaces=0, real_len, s_len = strlen(sentence);

    for(i=0; i<s_len; i++){
        if(sentence[i] == ' ' ||sentence[i] == 'j')
            ++spaces;
    }

    real_len = s_len - spaces;
    pos = malloc(sizeof(struct position)*real_len);

    for(i=0, w=0; i<s_len; i++){
        for(x=0; x<table_len; x++){
            for(y=0; y<table_len; y++){
		
		if(sentence[i] ==' '||sentence[i] == 'j')
		{
                    ++w;
		    ++i;
                }
		if(sentence[i] == table[x][y]){
                    pos[i-w].row = x;
                    pos[i-w].column = y;
                    //printf("%i%i ", pos[i-w].row, pos[i-w].column);
                }
  

            }
        }
    }

    return pos;
}

void Write_Data(char *filename, char *message)
{
        FILE *fp;

        if ((fp = fopen(filename, "w+")) == NULL)
        {
            printf ("Failed to create/open file %s\n", filename);
            exit (2);
        }
        fprintf (fp,"%s\n", message);
        fclose(fp);
}

void Read_Data(char *filename)
{
	FILE *fp;
	char *message;
        if ((fp = fopen (filename, "r")) == NULL)
        {
            printf ("Failed to open file %s\n", filename);
            exit (2);
        }
	while(fgets (message,50, fp) != NULL)  //Checking for EOF
	{
        	//fscanf (fp, "%s",message);
		printf("%s",message);
	}
        fclose (fp);
	//printf("%s",message);
	//return message;
}

int str_in(char *str1,char *str2)
{
	int i,j=0,k;
	for(i=0;str2[i];i++)
	{
		if(str2[i]==str1[j])
		{
			for(k=i,j=0;str2[k] && str1[j];j++, k++)
				if(str2[k]!=str1[j])
					break;
				if(!str1[j])
					return 1;
		}
	}
	return 0;
}

void signin(char filesnames[])
{
  char username[20];
  char userpwd[20];
  int i=0;
  //static int j=0;
  static int k=5;
  printf("Enter your username : ");
  //gets(username);
  scanf("%s",username);
  printf("Enter your password : ");
  /* accept password */
  char ch;
	while(ch!='\r')
	{
		ch=getch();
		if(ch!='\r')
		{
			userpwd[i]=ch;
			i++;
			printf("*");
		}
	}
  userpwd[i]='\0';
/*------------------*/
 
  printf("\n\nPress any key to continue");
  getch();
 
 if((!strcmp(username,"mayur") && !strcmp(userpwd,"mayur123"))||(!strcmp(username,"vineeth") && !strcmp(userpwd,"vineeth123"))||(!strcmp(username,"kaushik") && !strcmp(userpwd,"kaushik123"))||(!strcmp(username,"chintamani") && !strcmp(userpwd,"chintamani123")))
 {
  printf("\n\nLogged In Successful\n");
  strcpy(filesnames,username);
 }else
 {
  printf("\n\nIncorrect username or password");
  //j++;
  k--;
  if(k!=0)
  {
	printf("\nYou have %d more attempts to type the correct login credentials\n",k);
	signin(filesnames);
  }
  else 
  {
  	printf("\nYou have exceeded your limit\n");
	exit(2);
  } 
 }
 //strcpy(filesnames,username);
}

void Append(char filesnames[],char filename[])
{
	FILE *fr;
	char message[50];
	int chk=0;
	int len;

	len=strlen(filename);
	filename[len]='\n';
	filename[len+1]='\0';

	if ((fr = fopen (filesnames, "r")) == NULL)
        {
            printf ("Failed to open file %s\n", filesnames);
            exit (2);
        }
	while(fgets (message,50, fr) != NULL && chk==0)  //Checking for EOF
	{	
        	if(!(strcmp(filename,message)))
		{
			printf("\nGiven file name is already present in your account\n");
			chk=1;
			printf("\nLogging you out and ending....\n\n");
			exit(2);
		}
	}
	fclose (fr);
	if(chk==0)
	{
	FILE *fp; 
	if ((fp = fopen(filesnames, "a")) == NULL)
	{
            Write_Data(filesnames,filename);
        }
	//fscanf(fp,"%s",message);
	//if(!str_in(filename,message))
	
	//len=strlen(filename);
	//filename[len]='\n';
	//filename[len+1]='\0';
	fputs(filename,fp);
	printf("\nA new file has been successfully stored in your account(%s) as %s\n",filesnames,filename);
	
	/*else
	{
		printf("\nGiven file name is already present in the account\nTaking you back to the beginning of the program.....\n");
		//goto beg;
	}*/
	fclose (fp);
	}
	//fclose (fr);
}

/*
void signin(char filesnames[])
{
  char username[20];
  char userpwd[20];
  int i=0;
  //static int j=0;
  static int k=5;
  printf("Enter your username : ");
  //gets(username);
  scanf("%s",username);
  printf("Enter your password : ");
  char ch;
	while(ch!='\r')
	{
		ch=getch();
		if(ch!='\r')
		{
			userpwd[i]=ch;
			i++;
			printf("*");
		}
	}
  userpwd[i]='\0';
 
  printf("\n\nPress any key to continue");
  getch();
 
 if((!strcmp(username,"mayur") && !strcmp(userpwd,"mayur123"))||(!strcmp(username,"vineeth") && !strcmp(userpwd,"vineeth123"))||(!strcmp(username,"kaushik") && !strcmp(userpwd,"kaushik123"))||(!strcmp(username,"chintamani") && !strcmp(userpwd,"chintamani123")))
 {
  printf("\n\nLogged In Successful\n");
  strcpy(filesnames,username);
 }else
 {
  printf("\n\nIncorrect username or password");
  //j++;
  k--;
  if(k!=0)
  {
	printf("\nYou have %d more attempts to type the correct login credentials\n",k);
	signin(filesnames);
  }
  else 
  {
  	printf("\nYou have exceeded your limit\n");
	exit(2);
  } 
 }
 //strcpy(filesnames,username);
}
*/

void main() {
    char **table;
    char sentence[MAX_VALUE];
    char answ='y';
    char filename[50],f1[50];
    char filesnames[20];
    struct position *posXY;
    char* de_crypt_sen;
    int i, table_len, method = 0;
    table_len = 5;
    table = malloc(table_len * sizeof(char*));
    for (i = 0; i < table_len; i++)
        table[i] = malloc((table_len+1) * sizeof(char));
    table[0] = "abcde";
    table[1] = "fghik";
    table[2] = "lmnop";
    table[3] = "qrstu";
    table[4] = "vwxyz";
    signin(filesnames);
    while(answ=='y')   
    {
    printf("Do you want to cipher (0) or decipher (1)? : ");
    scanf("%i", &method);
    printf("\n");

    if(method == 0){ //cipher
        printf("\nNOTE:\nThe sentence should not contain 'j'\nYou can use 'i' as a substitute for 'j'\n\nWrite the sentence:");
        scanf(" %[^\n]s", sentence);
        printf("\n");
	printf("\nHere are the list of files in your account: \n");
	Read_Data(filesnames);

        /* CRYPTING... word: how are you
            h  o  w   a  r  e   y  o  u
            12 23 41  00 31 04  43 23 34
                            h o w  a r e  y o u
            Row(x)          1 2 4  0 3 0  4 2 3
            Column(y)       2 3 1  0 1 4  3 3 4
            12 40 30  42 32 31  01 43 34
            h  v  q   x  s  r   b  y  u
        */

        posXY = searchOnTable(table, sentence, table_len);

        printf("\n");

        de_crypt_sen = reverseSearchOnTable(table, sentence, posXY, table_len, method);
	
	
	printf("\nNOTE:\nFile should not already exist \nElse logs you out and terminates \n\nEnter the name of the file to be created\n");
	
	scanf("%s",filename);

	Write_Data(filename,de_crypt_sen);

	Append(filesnames,filename);
        
        printf("\n\nSentence is successfully Ciphered in your account(file) as %s\n",de_crypt_sen);

        system("PAUSE");
    }
    else if(method == 1){ //decipher
	
	printf("\nEnter the name of the file to be read from the list: \n");
	Read_Data(filesnames);
	scanf("%s",filename);
        printf("\nMessage is being read from your account (file)\n");
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)
        {
            printf("Failed to create/open file %s\n", filename);
            exit (2);
        }
	fscanf(fp,"%s",sentence);
	printf("Message in the file :%s",sentence);
	fclose(fp);
        printf("\n");

        /* DECRYPTING... word: hvq xsr byu
            h  v  q   x  s  r   b  y  u
            12 40 30  42 32 31  01 43 34
                            h v q  x s r  b y u
            Row(x)          1 4 3  4 3 3  0 4 3
            Column(y)       2 0 0  2 2 1  1 3 4
                            h o w  a r e  y o u
            Row(x)          1 2 4  0 3 0  4 2 3
            Column(y)       2 3 1  0 1 4  3 3 4
            12 23 41  00 31 04  43 23 34
            h  o  w   a  r  e   y  o  u
        */
        posXY = searchOnTable(table, sentence, table_len);

        printf("\n");

        de_crypt_sen = reverseSearchOnTable(table, sentence, posXY, table_len, method);

        printf("\n\nSentence is successfully Deciphered from %s to %s\n", sentence,de_crypt_sen);

        printf("\n");

        system("PAUSE");
    }
    else
    {
        printf("\nInvalid operation\n");
    }
    printf("Enter 'y' to continue, any other character to log out\n");
    scanf(" %c",&answ);
    }
    printf("Press any key to end\n");
    getch();
}