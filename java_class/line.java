public class line
{

    point first;
    point second;
	float m;
	float B;

    line()
    {
	first = new point();
	second = new point();
    }

    line(point a, point b)
    {
	first  = new point(a);
	second = new point(b);

    }

    void print_linear_f()
    {
	m = (first.yvalue-second.yvalue)/(first.xvalue-second.xvalue);
	B = second.yvalue-second.xvalue * m;

	System.out.print("y="+m+"x+"+B+"\n\n");
	


    }

};