
public class Pet { // Pet class with it's attributes.
	private String petType;
	private String petName;
	private int petAge;
	private int dogSpaces;
	private int catSpaces;
	private int daysStay;
	private double amountDue;

	public Pet() {
		petType = "None";
		petName = "None";
		petAge = -1;
		daysStay = -1;
	} // Basic constructor for the pet class with default values.
	
	// Mutator and Accessor for Pet Type.
	public void setPetType(String Type) {
		petType = Type;
	}
	public String getPetType() {
		return petType;
	}
	
	// Mutator and Accessor for Pet Name.
	public void setPetName(String Name) {
		petName = Name;
	}
	public String getPetName() {
		return petName;
	}
	
	// Mutator and Accessor for Pet Age.
	public void setPetAge(int Age) {
		petAge = Age;
	}
	public int getPetAge() {
		return petAge;
	}
	
	// Mutator and Accessor for Dog Spaces.
	public void setDogSpaces(int DogSpc) {
		dogSpaces = DogSpc;
	}
	public int getDogSpaces() {
		return dogSpaces;
	}
	
	// Mutator and Accessor for Cat Spaces.
	public void setCatSpaces(int CatSpc) {
		catSpaces = CatSpc;
	}
	public int getCatSpaces() {
		return catSpaces;
	}
	
	// Mutator and Accessor for Days Staying.
	public void setDaysStay(int Days) {
		daysStay = Days;;
	}
	public int getDaysStay() {
		return daysStay;
	}
	
	// Mutator and Accessor for Amount Due.
	public void setAmountDue(double Due) {
		amountDue = Due;
	}
	public double getAmountDue() {
		return amountDue;
	}
	
}
