#include <iostream>
#include <string>
#include <vector>
#include <memory>

//Andrew Dowd//

using namespace std;

class Pet {
   public:
      //constructor
    Pet(string name, int age){

        this->Name = name;
        this->Age = age;
    }

      //setters
      void SetName(string newName) {
          Name = newName;
      }

      void SetAge(int newAge) {
          Age = newAge;
      }

      //getters
      string GetName(){
          return Name;
      }
      int GetAge(){
          return Age;
      }

        //methods
      virtual void Display()  {
        cout << "Name: " << Name << " Age: " << Age << endl;
      }
    //variables
   protected:
      string Name;
      int Age;

};

class IndoorPet : public Pet {
   public:
    //constructor
    IndoorPet(string species, string Name, int Age):Pet(Name, Age){
        this->Name = Name;
        this->Age = Age;
        this->Species = species;
    }

    //setters
      void SetSpecies(int newSpecies) {
          Species = newSpecies;
      }
    //getters
      string GetSpecies() {
          return Species;
      }
    //methods3
      virtual void Display()  {
        cout << "Name: " << Name << " Age:" << Age << " Species: " << Species << endl;
      }

    //variables
   protected:
      string  Species;
};

string CheckName(){ //checks the name input and returns it to main
    string name = "";
    bool correctName = false;

    while(correctName == false){
    cout << "Enter the pets name: " ;
    cin >> name;

        if(name == ""){
            cout << "Error you didn't enter a name" <<endl;
        }
        else{
            correctName = true;
        }


    }
    return name;
}

int CheckAge(){ //checks the age input and returns it to main
    string inputedAge;
    int age;
    bool correctAge = false;
    while(correctAge == false){
        cout << "Enter the pets age: ";
        cin >> inputedAge;
        if(sscanf(inputedAge.c_str(), "%d", &age) == 1){
            correctAge = true;
        }
        else if(age <= 0){
            cout << "Error you didnt enter a number above 0" << endl;
        }
        else{
            cout << "Error you didnt enter a proper number" << endl;
        }
    }
    return age;
}

string CheckSpecies(){ //checks species input and returns it to main
    string species = "";
    bool correctSpecies = false;

    while(correctSpecies == false){
    cout << "Enter the pets species: " ;
    cin >> species;

        if(species == ""){
            cout << "Error you didn't enter a pet species" <<endl;
        }
        else{
            correctSpecies = true;
        }


    }

    return species;
}


void PrintMenu(){ //prints main menu
    cout << "Main menu: Select an option." << endl;
    cout << "1.  Add pet" << endl;
    cout << "2.  Remove pet" << endl;
    cout << "3.  Display all items " << endl;
    cout << "4.  End the program " << endl;

}

void PrintAddMenu(){ //prints add menu
    cout << "What type of pet will be added?" << endl;
    cout << "1 Pet " << endl;
    cout << "2 Indoor Pet" << endl;
    cout << "3 Quit back to the menu" << endl;
}
int main()
{
    //object declaration
    vector<unique_ptr<Pet>> pets;

    //variables for pet
    string petName;
    int petAge;

    //variables for indoorpet
    string indoorPetName;
    int indoorPetAge;
    string indoorPetSpecies;

    int index = 0; // for recording the max number of items inputed

    //variable declaration
    string userInput; // preconvert user input
    int uInput; // the convereted users input

    //add input variables
    string addInput;
    int aInput;

    // remove input variables
    string removeInput;
    int rInput;



    //verification variables
    bool programOn = true; // keeps the program on until the user quits
    bool correctAddOption = false; // verifys the adding input
    bool correctRemoveOption = false; // verifys the remove input


    //code

    while(programOn == true){ //keeps the program on and running

        PrintMenu();

        cin >> userInput;

        if(sscanf(userInput.c_str(), "%d", &uInput) == 1){ //correct input looper
            //if statement to check for 1 - 4 inputs
            if(uInput == 1){ // adding section
                while(correctAddOption == false){ //
                PrintAddMenu();
                cin >> addInput;
                if(sscanf(addInput.c_str(), "%d", &aInput) == 1){
                    if(aInput == 1){ //makes new pet
                        correctAddOption = true;

                        petName = CheckName();

                        petAge = CheckAge();
                        //cout << petName << " " << petAge << endl;

                        pets.push_back(make_unique<Pet>(petName, petAge));
                        index++;
                    }
                    else if(aInput == 2){ //makes new indoor pet
                        correctAddOption = true;
                        indoorPetName = CheckName();
                        indoorPetAge = CheckAge();
                        indoorPetSpecies = CheckSpecies();

                        //cout << indoorPetName << " " << indoorPetAge << " " << indoorPetSpecies << endl;

                        pets.emplace_back(make_unique<IndoorPet>(indoorPetName, indoorPetSpecies , indoorPetAge));

                        index++;
                    }

                    else if(aInput == 3){
                        correctAddOption = true;
                        cout << "Returning to the menu" << endl;
                    }
                    else{ cout << "Error your input isn't an option on the menu" << endl; }

                }
                else{ cout << "Error you didn't enter a proper number" << endl; }
                }
                correctAddOption = false;
            }
            else if(uInput == 2){ // remove section
                while(correctRemoveOption == false){
                    cout << "Enter the index of the item you want to remove or enter q to go back to the menu" << endl; // using q instead of a negative number or another number due to the fact the index can be anything
                    cin >> removeInput;

                    if(removeInput == "q" || removeInput == "Q"){ //checking for both versions of q
                        cout << "Returning to the menu" << endl;
                        correctRemoveOption = true;
                    }
                    else if(rInput > index){ //stops if the input is bigger than index
                        cout << "Error you entered number outside of the max index " <<endl;


                    }
                    else if(sscanf(removeInput.c_str(), "%d", &rInput) == 1){ //input validation
                        correctRemoveOption = true;
                        pets.erase(pets.begin() + rInput);
                        index--;
                    }
                    else{
                        cout << "Error you didn't enter a proper number or q" << endl;
                    }
                }
                    correctRemoveOption = false;
            }
            else if(uInput == 3){ //printing section
                cout << "Displaying all items" << endl;

                for (auto& pet: pets) {
                    pet->Display();
                }
            }
            else if(uInput == 4){ //turns off the program
                programOn = false;
                cout << "Thank you for using the program have a nice day!" << endl; }
            else{ cout << "Error your input isn't an option on the menu" << endl; } // telling the user they misinputed

        }
        else{ //error message for main menu
            cout << "Error you didn't enter a proper number" << endl;
        } //telling the user they didn't input a actual number

        }

} //while program on ending

//Problem statement//
/*My code is meant to help make a registry of pets and indoor pets*/
