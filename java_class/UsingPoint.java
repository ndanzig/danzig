
public class UsingPoint {


	public static void main(String[] args) {
		

	    String one="hi mom ";
	    System.out.println(one + one );


	    simplePoint mypoint = new simplePoint();
	    mypoint.xvalue=10;
	    System.out.println("Xvalue: " + mypoint.xvalue + "\nYvalue: " + mypoint.yvalue + "\n"  );



	    point mypoint2 = new point();
	    mypoint2.xvalue=89;	    
	    System.out.println("Xvalue: " + mypoint2.xvalue + "\nYvalue: " + mypoint2.yvalue + "\n"  );


	    point mypoint3 = new point(49,94);
	    mypoint3.xvalue=89;	    
	    System.out.println("Xvalue: " + mypoint3.xvalue + "\nYvalue: " + mypoint3.yvalue + "\n"  );


	    point mypoint4 = new point(55555);
	    
	    System.out.println("Xvalue: " + mypoint4.xvalue + "\nYvalue: " + mypoint4.yvalue + "\n"  );



	}

}
