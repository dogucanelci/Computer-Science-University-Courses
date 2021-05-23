/* @Author
Student Name: <Dogu Can  ELCI>
Student ID : <504201516>
Date: <09.12.20> */

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <fstream>

using namespace std;

struct resistor{
char group;
double value;
int quantity;
int counter=0;
resistor *next;
};

struct Circuit{
resistor *head;
void create();
Circuit add_resistor(Circuit);
int remove_resistor(Circuit,char,int);
void delete_resistor(resistor *);
void circuit_info(Circuit,int);
void quantity_print(Circuit,int);
void clear();
};

void Circuit::create(){ //Creates the circuit(resistor list).

    head=NULL;
    
}


int Circuit::remove_resistor(Circuit circ_list,char group,int nodenumb){//Removes a resistor from the circuit.
	resistor *trav_1=new resistor;
	resistor *prev1=new resistor;
	bool cont=false;
	trav_1=circ_list.head;
	prev1=trav_1;
	while (trav_1->group!=group)
	{	prev1=trav_1;
		trav_1=trav_1->next;
		cont=true;
	}

		if(!cont){
			circ_list.head=circ_list.head->next;
			cont=false;
		}
		else{
			prev1->next=trav_1->next;
			return 0;
		}
return 0;
}

void Circuit::delete_resistor(resistor *deleted){  //It deletes the resistor node from the circuit.
	delete[] deleted;
	
}

void Circuit::circuit_info(Circuit crc_list,int nodenumb){

		resistor *trav_i;
		trav_i=head;
		while(trav_i!=NULL){
		resistor *trav_j;
		trav_j=trav_i;
		trav_j=trav_j->next;
			while(trav_i!=NULL){
			trav_j=trav_i->next;
			while((trav_i) && (trav_j)&&trav_i->group!=trav_j->group){
				trav_j=trav_j->next;
			}
			if(trav_j!=NULL){
				trav_j->quantity++;
				crc_list.remove_resistor(crc_list,trav_i->group,nodenumb);
				*(&nodenumb)=nodenumb-1;
				trav_i=trav_i->next;
				continue;
			}

			else{
				trav_i=trav_i->next;
				continue;
			}	
		}
	}
	resistor *trav;
	resistor *prev;
	trav=new resistor;
	prev=new resistor;
	trav=crc_list.head;
	crc_list.quantity_print(crc_list,nodenumb);
	int no_res_counter=0;
	bool cont=false;
	/*
	while(trav!=NULL){ //insert as a first node to no_resistor kac tane no_res old. sayiyor.
		if(trav->quantity>=0){
			prev=trav;
			trav=trav->next;
			continue;
		}
		no_res_counter=no_res_counter+-1*trav->quantity;
		trav=trav->next;
	}
	*/
	trav=new resistor;
	prev=new resistor;
	trav=crc_list.head;
	while(trav!=NULL){	
		if(trav->quantity>=0){
			if(prev->value!=trav->value){
				if(trav->quantity==0){
					trav->counter=0;
					trav=trav->next;
					continue;
				}
			if(!cont){
				for(int i=0;i<no_res_counter;i++){
				cout<<"NO_RESISTOR"<<endl;
				cont=true;
			}
			}
			
			cout<<trav->value<<":"<<trav->quantity+trav->counter<<endl;
			trav->counter=0;
			prev=trav;
			trav=trav->next;
			
			}
			else{

				trav=trav->next;
			}
		}
		else{
			//cout<<"NO_RESISTOR"<<endl;
			trav=trav->next;
		}
	}
	
	if(trav==NULL){ //sona ilerlemisse total bastirmak icin
	resistor *trav1=new resistor;
	double total_res=0;
	trav1=head;
	while(trav1!=NULL){
		if(trav1->quantity>0 && trav1->value>0){
			total_res=total_res+(trav1->value/trav1->quantity);
		}	
		trav1=trav1->next;
	}
	cout<<"Total resistance="<<total_res<<" ohm"<<endl;
}

	//icinde remove ve delete ve add fonk. tasir ve list i A0 a kadar olan yere kadar gunceller.
	//Prints the resistor info and total resistance in the circuit (workflow 3).

}

void Circuit::quantity_print(Circuit crc_list,int nodenum){
	resistor *trav_i;
	resistor *trav_j;
	trav_i=crc_list.head;
	if(trav_i==NULL){
		return;
	}
	trav_j=trav_i->next;
	while(trav_i!=NULL){ //counter yani value sayici fonksiyonu(ornegin 2 degerini tasiyan 3 grup var vs.)
		while(trav_j!=NULL){
			if(trav_i->value==trav_j->value){
				trav_i->counter=trav_i->counter+trav_j->quantity;
			}
			trav_j=trav_j->next;
		}
		trav_i=trav_i->next;
		if(trav_i){
			trav_j=trav_i->next;
		}			
	}
	}
	

Circuit Circuit::add_resistor(Circuit crc_list){ //Adds a resistor to the circuit (workflow 1).
	int nodenumb=0;
	fstream reader;
    reader.open("input.txt", fstream::in | fstream::binary);
	char group_name; //txt den cekilecek grup chari 
	double res_val;	//txt den cekilecek  resistor degeri
	while(!reader.eof()){
		resistor *traverse;
		resistor *prev;
		resistor *newres=new resistor;
		reader>>group_name>>res_val; //degerler txt den cekiliyor.
		newres->group=group_name;
		newres->value=res_val;
		newres->quantity=1;
		traverse=crc_list.head;
		prev=traverse;
		if(group_name=='A' && res_val==0){
			crc_list.circuit_info(crc_list,nodenumb); //crc_list koymak anlamsiz
			continue;
		}
		if (crc_list.head==NULL){	//ilk ekleme
			if(newres->value<0){
				cout<<"NO_RESISTOR"<<endl;
			}
			crc_list.head=new resistor;
			crc_list.head=newres;
			crc_list.head->next=NULL;
			nodenumb++;	
		}
		else
		{		
			if(newres->value<0){
					while(traverse && traverse->value<-1*newres->value){
					prev=traverse;
					traverse=traverse->next; // gösterdiği adres değişiyor.
					}
				}
			
			else{
				while(traverse && traverse->value<newres->value){
					prev=traverse;
					traverse=traverse->next; // gösterdiği adres değişiyor.
				}
			}

				if(traverse){
					if(traverse->group==newres->group){	//ayni grup value lari ayni oldugu icin kullanilabilir.
						if(newres->value<0){
							if(traverse->quantity>0){
								traverse->quantity--;
								continue;
							}
							cout<<"NO_RESISTOR"<<endl;			
							nodenumb++;
							continue;
						}
						else{
						traverse->quantity++;	//deger atanmiyor,mevcut eleman quantity si degisiyor.				
						nodenumb++;
						continue;
						}
					}
					else if(newres->value<=traverse->value && traverse!=prev){
						prev->next=newres;
						newres->next=traverse;
						nodenumb++;
						continue;
					}

					else if(newres->value<=traverse->value){
						newres->next=crc_list.head;
						crc_list.head=newres;
						nodenumb++;
						continue;
					}
					
				}
				
				else{
					prev->next=newres; //input en buyuk
					nodenumb++;
					newres->next=NULL;
					continue;
				}
		}
	}
	return crc_list;
}

void Circuit::clear(){   //Deletes all of the nodes of the list (workflow 4).
	while(head){
	resistor *newres=new resistor;
	newres=head;
	head=head->next;
	delete newres;
	}
}


int main(){
    Circuit crc_list;
    crc_list.create();
	Circuit crc_list1=crc_list.add_resistor(crc_list);
	crc_list1.clear();
	//system("pause");
return 0;
}





