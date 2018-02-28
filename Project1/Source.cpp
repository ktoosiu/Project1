#define _USE_MATH_DEFINES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <math.h>
const double PI = 3.1415926535897932384650288;

// Pocztkowy rozmiar i pozycja 15-kata
GLfloat polyX = 100.0f;
GLfloat polyY = 150.0f;
GLsizei polyRadius = 50.0f;

// Rozmiar kroku (liczba pikseli) w osi x i y
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;
// Dane zmieniajcych si� rozmiar�w okna
GLfloat windowWidth;
GLfloat windowHeight;

GLfloat rotacja = 30.0f;

///////////////////////////////////////////////////////////
// Wywo�ywana w celu przerysowania sceny
void RenderScene(void) {
	// Wyczyszczenie okna aktualnym kolorem czyszcz�cym
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(polyX, polyY, 0.0f);
	glRotatef(rotacja, 0.0f, 0.0f, -1.0f);
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0f, 0.0f);
	int ile = 14;//+1=15
	GLfloat kat;
	for (int i = 0; i <= ile; i++)//rysowanie wielokata
	{
		kat = i * 2.0f * PI / ile;
		glVertex2f(cos(kat)*polyRadius, sin(kat)*polyRadius);
	}
	glEnd();
	glPopMatrix();
	// Wys�anie polece� do wykonania - !!! dla animacji to jest inne polecenie
	glutSwapBuffers();
	rotacja += 1.0f;
}
// Wywo�ywana przez bibliotek GLUT w czasie, gdy okno nie
// jest przesuwane ani nie jest zmieniana jego wielko��
void TimerFunction(int value) {
	// Odwr�cenie kierunku, je�eli osi�gni�to lew� lub praw� kraw�d�
	if (polyX > windowWidth - polyRadius || polyX < -1.0 * windowHeight / windowWidth + polyRadius)
		xstep = -xstep;

	// Odwr�cenie kierunku, je�eli osi�gni�to doln� lub g�rn� kraw�d�
	if (polyY > windowHeight - polyRadius || polyY < -1.0 * windowHeight / windowWidth + polyRadius)
		ystep = -ystep;


	// Kontrola obramowania. Wykonywana jest na wypadek, gdyby okno     
	// zmniejszy�o swoj wielko�� w czasie, gdy kwadrat odbija� si� od     
	// kraw�dzi, co mog�oby spowodowa�, �e znalaz� by si� poza      
	// przestrzeni� ograniczajc�.     
	if (polyX > windowWidth - polyRadius)
		polyX = windowWidth - polyRadius - 1;

	if (polyY > windowHeight - polyRadius)
		polyY = windowHeight - polyRadius - 1;

	// Wykonanie przesuni�cia poly
	polyX += xstep;
	polyY += ystep;

	// Ponowne rysowanie sceny z nowymi wsp�rz�dnymi  
	glutPostRedisplay();
	glutTimerFunc(33, TimerFunction, 1);
}
///////////////////////////////////////////////////////////
// Konfigurowanie stanu renderowania
void SetupRC(void) {
	// Ustalenie br�zowego koloru czyszcz�cego     
	glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
}
///////////////////////////////////////////////////////////
// Wywo�ywana przez bibliotek GLUT przy ka�dej zmianie wielko�ci okna
void ChangeSize(GLsizei w, GLsizei h) {
	// Zabezpieczenie przed dzieleniem przez zero
	if (h == 0)
		h = 1;

	// Ustalenie wielko�ci widoku zgodnego z rozmiarami okna
	glViewport(0, 0, w, h);

	// Ustalenie uk�adu wsp�rz�dnych
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Keep the square square, this time, save calculated
	//// width and height for later use
	if (w <= h)
	{
		windowHeight = 250.0f*h / w;
		windowWidth = 250.0f;
	}
	else
	{
		windowWidth = 250.0f*w / h;
		windowHeight = 250.0f;
	}

	// Ustanowienie przestrzeni ograniczaj�cej (lewo, prawo, d�, g�ra, blisko, daleko)
	glOrtho(0.0f, windowWidth, 0.0f, windowHeight, 1.0f, -1.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
///////////////////////////////////////////////////////////
// G��wny punkt wej�cia programu
void main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Moj pierwszy program w GLUT");
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(33, TimerFunction, 1);
	SetupRC();
	glutMainLoop();
}