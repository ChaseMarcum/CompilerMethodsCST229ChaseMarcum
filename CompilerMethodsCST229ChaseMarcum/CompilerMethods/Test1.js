// ReSharper disable once WrongExpressionStatement
#define Number = 1;

// I do not want this line

function Person(firstname, lastname, age, eyecolor)
{
	this.firstname = firstname;
	this.lastname = lastname;
	this.age = age;
	this.eyecolor = eyecolor;
}

myFather = new Person("John","Doe",50,"blue");

document.write(myFather.firstname + " is " + myFather.age + " years old.");