package project13_2;

public class Cinnamon extends CondimentDecorator{
	/* your code */
	Beverage beverage;
	
	public Cinnamon(Beverage bev) {
		this.beverage=bev;
	}
	public String getDescription() {return beverage.getDescription() + ", Cinnamon";}
	public double cost() {return .50 + beverage.cost();}
}
