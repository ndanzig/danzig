public class point
{

     int xvalue;
    int yvalue;

    point(){
	xvalue=1;
	yvalue=1;

    }

    point(int x, int y)
    {

	xvalue=x;
	yvalue=y;
}


    point(int x)
    {

	xvalue=x;
	yvalue=1;
}


    point (point other)
    {

	xvalue=other.xvalue;
	yvalue=other.yvalue;

}



};