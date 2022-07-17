#include "HugeInteger.h"
#include <vector>
#include <random>
using namespace std;
#include <chrono>
using namespace std::chrono;


HugeInteger::HugeInteger(const std::string& val) {

	sign=0;
	//cout<<"Input String: "+val+"\n";

	//changes indicator to show number is negative
	if(val[0]=='-'){
		sign=1;
	}

	//checking for any errors in input
	int stringError=0;
	for(int i=sign;val[i]!='\0';i++){
		//checks if string has a char that is not 0-9
		if(val[i]>('9')||val[i]<('0')){
			//printf("ERROR DETECTED\n");
			stringError=1;
			break;
		}
	}




	//throws error if string is empty or an invalid integer
	if(val==""||stringError==1){
		throw std::invalid_argument("[testConstructorString] testType error");
	}
	else{
		//runs the entire length of string
		for(int i=sign;val[i]!='\0';i++){

			//adds each digit to vector
			hugeInt.push_back(val[i]-'0');
		}
	}

	//cout<<to_string(sizeof(hugeInt[0]))+"\n";
}

HugeInteger::HugeInteger(int n) {
	//handles case where input is invalid
	if(n<1){

		throw std::invalid_argument("[testConstructorNumber] testType error");
	}
	else{
		//new seed for random number every time program is run
		srand((unsigned) time(NULL));

		//sign set to positive number
		sign=0;

		//keeps track of number to be added
		int numAdded;
		//runs n times
		for(int i=0;i<n;i++){
			//gets a random number from 0-9
			numAdded=rand()%9;
			//if the first number is to be 0, change it to a 1
			if(i==0&&numAdded==0)
				numAdded+=1;
			//add the number to the vector
			hugeInt.push_back(numAdded);
		}
	}


}

HugeInteger HugeInteger::add(const HugeInteger& h) {

	string outputStr="";


	//temp output
	HugeInteger newInt=HugeInteger(1);

	//keeps track of how far along each int the program is
	int counter1=1;
	int counter2=1;

	//keeps track of each decimal place being added
	int addedNum1=0;
	int addedNum2=0;



	//keeps track of decimal place total and if there is a carry to next decimal point
	int carry=0;
	int total=0;

	//if the signs are different, call subtract function to perform calculation
	if(sign!=h.sign){

		HugeInteger temph =  h;
		temph.sign=sign;
		newInt=subtract(temph);

	}
	else{
	//runs only if at least one number still needs to be added
	//each loop represents adding the next greatest decimal point
	while(counter1<=h.hugeInt.size()||counter2<=hugeInt.size()){

		//resets to 0 each loop
		addedNum1=0;
		addedNum2=0;

		//gets two numbers to be added each loop from each vector
		//if all decimal places in hugeInt has been added, stays as zero, as the other number is added
		if(counter1<=h.hugeInt.size()){
			addedNum1=h.hugeInt.at(h.hugeInt.size()-counter1);
		}
		if(counter2<=hugeInt.size()){
			addedNum2=hugeInt.at(hugeInt.size()-counter1);
		}

		//adds the two decimal places together as well as the carry if there is one
		total=addedNum1+addedNum2+carry;

		//if the total is > 9, a carry is needed so carry=1 and total is subtracted 10
		//if < 9, no carry is needed so carry =0 and total is unchanged
		if(total>9){
			carry=1;
			total-=10;
		}
		else{
			carry=0;
		}

		//the total is added to end of string
		//this number would be in reverse since program is starting from least sig to most sig
		outputStr=outputStr+to_string(total);


		//counters that keep track of which decimal place loop is on are incremented
		counter1++;
		counter2++;
	}

	//if there still a carry at end of operation, it is added to end of string
	if(carry==1){
		outputStr=outputStr+to_string(carry);
	}

	//reverses string output to used in hugeInteger object
	reverse(outputStr.begin(),outputStr.end());


	newInt =  HugeInteger(outputStr);


	//if both signs are negative, return negative number
	if(sign==1&sign==1)
		newInt.sign=1;

	}




	return newInt;
}

HugeInteger HugeInteger::subtract(const HugeInteger& h) {


	//output
	HugeInteger newInt=HugeInteger("0");

	//if signs are different, call addition to perform calculation
	if(sign!=h.sign){



		int temp=sign;
		sign=h.sign;

		newInt=add(h);
		sign=temp;
		newInt.sign=temp;
	}
	else{

		//find larger int
		int larger=-1;

		if(hugeInt.size()>h.hugeInt.size())
			larger=1;
		else if(hugeInt.size()<h.hugeInt.size())
			larger=-1;
		else{

			//size is the same
			int same_digit=0;
			for(int i=0;i<hugeInt.size();i++){
				if(hugeInt[i]>h.hugeInt[i]){
					larger=1;
					break;
				}
				if(hugeInt[i]==h.hugeInt[i])
					same_digit++;
			}
			if(same_digit==hugeInt.size())
				larger=0;

		}
		//temp h so it can be pointed to using pointer
		HugeInteger temph=h;

		//assigning smaller and larger int values
		std::vector<int> *largerInt;
		std::vector<int> *smallerInt;
		if(larger==1){
			largerInt=&hugeInt;
			smallerInt=&temph.hugeInt;
		}
		else{
			largerInt=&temph.hugeInt;
			smallerInt=&hugeInt;
		}

		string outputStr="";

		//keeps track of how far along each int the program is
		int counter1=1;
		int counter2=1;

		//keeps track of each decimal place being added
		int subNum1=0;
		int subNum2=0;



		//keeps track of decimal place total and if there is a carry to next decimal point
		int carry=0;
		int total=0;

		//runs only if at least one number still needs to be added
		//each loop represents adding the next greatest decimal point
		while((counter1<=largerInt->size()||counter2<=smallerInt->size())){

			//resets to 0 each loop
			subNum1=0;
			subNum2=0;

			//gets two numbers to be added each loop from each vector
			//if all decimal places in hugeInt has been added, stays as zero, as the other number is added
			if(counter1<=largerInt->size()){
				subNum1=largerInt->at(largerInt->size()-counter1);
			}
			if(counter2<=smallerInt->size()){
				subNum2=smallerInt->at(smallerInt->size()-counter1);
			}

			//adds the two decimal places together as well as the carry if there is one
			total=subNum1-subNum2-carry;

			//if the total is > 9, a carry is needed so carry=1 and total is subtracted 10
			//if < 9, no carry is needed so carry =0 and total is unchanged
			if(total<0){
				carry=1;
				total+=10;
			}
			else{
				carry=0;
			}

			//the total is added to end of string
			//this number would be in reverse since program is starting from least sig to most sig
			outputStr=outputStr+to_string(total);


			//counters that keep track of which decimal place loop is on are incremented
			counter1++;
			counter2++;
		}

		//removes any zeros at the front of number
		for(int i=0;(outputStr[outputStr.size()-1]=='0'&&outputStr.size()>1);i++)
			//if(outputStr[outputStr.size()-1]=='0'&&outputStr.size()>1)
				outputStr.pop_back();



		//if the numbers are equal make the answer 0
		if(larger==0)
			outputStr="0";


		if(sign==1&&h.sign==1&&larger==1&&(outputStr!="0")){
			outputStr=outputStr+"-";
		}


		if(((sign==1&&h.sign==0)||(sign==0&&h.sign==0&&larger==-1))&&(outputStr!="0")){
			outputStr=outputStr+"-";
		}

		//reverses string output to used in hugeInteger object
		reverse(outputStr.begin(),outputStr.end());



		newInt =  HugeInteger(outputStr);

	}



	return newInt;
}

HugeInteger HugeInteger::multiply(const HugeInteger& h) {

	/*
	 *
	 * This method uses the Karatsuba multiplication with a running time of : (n^(log(3)/log2))
	 *
	 * Ex: 1234x5678
	 *
	 * step1 : divide number into 4 parts
	 * a=12
	 * b=34
	 * c=56
	 * d=78
	 *
	 * step2: axc=672
	 * step3: bxd=2652
	 * step4: (a+b)(c+d)=6164
	 * step5: step4-step1-step2 =2840
	 *
	 * step6: step2(10^n)+step5(10^(n/2))+step3 (n=number of terms)
	 *
	 * final answer: 7006652
	 */


	HugeInteger newInt=HugeInteger("0");


	//base case: if both numbers are one digit, multiply them normally
	if(hugeInt.size()==1&&h.hugeInt.size()==1){
		//multiplies single digit number normally and makes new object to be returned
		newInt=HugeInteger(to_string(hugeInt.at(0)*h.hugeInt.at(0)));
	}

	//base case: if being multiplied by zero, return 0
	else if(toString()=="0"||h.hugeInt[0]==0){    //can't use toString for object h, so just checking if first element is zero
		newInt=HugeInteger("0");
	}


	else{

		int n=0;

		//finds the size of the larger number and stores it in n
		if(hugeInt.size()>h.hugeInt.size())
			n=hugeInt.size();

		else if(hugeInt.size()<h.hugeInt.size())
			n=h.hugeInt.size();
		else
			n=hugeInt.size();


		//half of n to use in later in calculation
		int nHalf= n/2;

		//rounds up if n is an odd number
		if(n%2!=0){
			nHalf+=1;
		}



		string a="";
		string b="";

		//splits the first number into 2 parts
		for(int i=0;i<hugeInt.size();i++){


			if(hugeInt.size()==1){
				a="0";

				if(hugeInt[0]==0){
					b="0";
				}
				else
					b=to_string(hugeInt[0]);

			}
			else if(hugeInt.size()<nHalf){
				b=b+to_string(hugeInt[i]);
				a="0";

			}
			else if(i<(hugeInt.size()-nHalf)){
				//cout<<"ran\n";
				a=a+to_string(hugeInt[i]);
				//cout<<"xH: "+x_H+"\n";
			}
			else
				b=b+to_string(hugeInt[i]);
		}

		string c="";
		string d="";
		//splits second number into 2 parts
		for(int i=0;i<h.hugeInt.size();i++){

			if(h.hugeInt.size()==1){
				c="0";

				if(h.hugeInt[0]==0){
					d="0";
				}
				else
					d=to_string(h.hugeInt[0]);

			}
			else if(h.hugeInt.size()<nHalf){
				d=d+to_string(h.hugeInt[i]);
				c="0";

			}
		else if(i<(h.hugeInt.size()-nHalf))
				c=c+to_string(h.hugeInt[i]);
			else
				d=d+to_string(h.hugeInt[i]);
		}



//sets each variable to 0 if it is empty
		if(a=="")
			a="0";
		if(b=="")
			b="0";
		if(c=="")
			c="0";
		if(d=="")
			d="0";


		//removes all leading zeros
		string letters[4]={a,b,c,d};
		string letters_noZeros [4];
		int nonzeroDetected=0;
		string temp="";
		for(int letterCount=0;letterCount<4;letterCount++){

			string temp_letter=letters[letterCount];
			nonzeroDetected=0;
			temp="";

			for(int i=0;i<temp_letter.size();i++){

			    if((temp_letter[i]>='1'&&temp_letter[i]<='9'))
			        nonzeroDetected=1;

			    if(nonzeroDetected==1){
			        temp=temp+temp_letter[i];
			    }
			}
			if(temp=="")
				temp="0";
			letters_noZeros[letterCount]=temp;
		}

		//stores elements for nonzero array to each indiv letter
		a=letters_noZeros[0];
		b=letters_noZeros[1];
		c=letters_noZeros[2];
		d=letters_noZeros[3];

		//stores each string into hugeInt object
		HugeInteger a_object=HugeInteger(a);
		HugeInteger b_object=HugeInteger(b);
		HugeInteger c_object=HugeInteger(c);
		HugeInteger d_object=HugeInteger(d);


		//step 1: multiply a and c
		HugeInteger a_x_c = a_object.multiply(c_object);


		//step 2: multiply b and d
		HugeInteger b_x_d = b_object.multiply(d_object);


		//step 3: do the calculation: (a+b)(c+d)
		HugeInteger ab_added=a_object.add(b_object);
		HugeInteger cd_added=c_object.add(d_object);
		HugeInteger ab_x_cd = ab_added.multiply(cd_added);


		//step 4: do calculation: step3-step1-step2
		HugeInteger ab_x_cd_MINUS_b_x_d= ab_x_cd.subtract(b_x_d);
		HugeInteger ab_x_cd_MINUS_b_x_d_MINUS_a_x_c= ab_x_cd_MINUS_b_x_d.subtract(a_x_c);


		//multiply step1 by 10^n
		for(int i=0;i<(nHalf*2);i++){
			a_x_c.hugeInt.push_back(0);

		}

		//multiply step4 by 10^(n/2)
		for(int i=0;i<(nHalf);i++){
			ab_x_cd_MINUS_b_x_d_MINUS_a_x_c.hugeInt.push_back(0);
		}


		//add steps 1(10^n),2,4(10^(n/2)) together
		HugeInteger step1_plus_2=b_x_d.add(a_x_c);

		newInt=step1_plus_2.add(ab_x_cd_MINUS_b_x_d_MINUS_a_x_c);

		//removes leading zero
		if(newInt.hugeInt[0]==0&&newInt.hugeInt.size()!=1){
			newInt.hugeInt.erase(newInt.hugeInt.begin());
		}
}

	//removes leading zero
	if(newInt.hugeInt[0]==0&&newInt.hugeInt.size()!=1){
		newInt.hugeInt.erase(newInt.hugeInt.begin());
	}


	//sets sign for the number
	if(sign!=h.sign&&toString()!="0"&&h.hugeInt[0]!=0)
		newInt.sign=1;

//returns new number
	return newInt;
}

int HugeInteger::compareTo(const HugeInteger& h) {


	int equal=0;

	//case: when signs are different
	if(sign!=h.sign){
		if(sign<h.sign)
			equal=1;
		else
			equal=-1;
	}
	else{
		//printf("signs are same: %d  %d\n",sign,h.sign);
		if(hugeInt.size()>h.hugeInt.size())
			equal=1;
		else if(hugeInt.size()<h.hugeInt.size())
			equal=-1;
		//case: same sign, same size
		else{
			//printf("same size +sign:\n");
			equal=-1;
			int same_digit=0;
			for(int i=0;i<hugeInt.size();i++){
				if(hugeInt[i]>h.hugeInt[i]){
					equal=1;
					break;
				}
				if(hugeInt[i]==h.hugeInt[i])
					same_digit++;
			}
			if(same_digit==hugeInt.size())
				equal=0;
		}
	}

	//flips the sign if both numbers are negative
	if(sign==1&&h.sign==1)
		equal*=-1;

	return equal;
}

std::string HugeInteger::toString() {

	std::string hugeString="";

	//adds a minus sign is the number is negative
	if(sign==1)
		hugeString=hugeString+"-";
	//loops through whole vector and adds each element to string
	for(int i=0;i<hugeInt.size();i++){
		hugeString=hugeString+to_string(hugeInt.at(i));

	}
	//cout<<"\nOUTPUT STRING: ("+hugeString+")\n";

	return hugeString;
}


double HugeInteger::HugeIntTiming(){

	system_clock::time_point startTime, endTime;
	int MAXNUMINTS=100; //controls how many numbers are inputted
	int MAXRUN=100;
	double runTime=0.0;
	double durationMs=0.0;
	int n = 500;
	for (int numInts=0; numInts < MAXNUMINTS; numInts++){
		HugeInteger huge1(n); //creates a random integer of n digits
		HugeInteger huge2(n); //creates a random integer of n digits
		startTime = system_clock::now();
		for(int numRun=0; numRun < MAXRUN; numRun++){
			HugeInteger huge3 = huge1.add(huge2);
		}
		endTime = system_clock::now();
		durationMs = (duration<double, std::milli>(endTime - startTime)).count();
		printf("%f\n",durationMs);
		runTime += durationMs/((double)MAXRUN);
	}
	runTime = runTime/((double)MAXNUMINTS);

	printf("runtime: %f\n",runTime);

	return 0.0;
}

