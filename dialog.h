//Madhusudhan Ramakrishnaiah - A04735682

#ifndef DIALOG_H
#define DIALOG_H

//header file that contains all classes used in this assignment-l1,so no forward declarations necessary
#include <QtGui>
#include "glwidget.h"
#include <ploting.h>


class ca : public QDialog
{
    Q_OBJECT

public:

    float A,B,C,T;

    ca(QWidget *parent = 0);

    void create_PushButton();

    void create_label();

    void create_radiobutton();

    void create_combobox();

    void create_spinbox();

    void create_layout();

    void create_lineedit();

    void create_dockwidget();

    void create_menuactions();

    void create_menu();

    //to show cache simulation output
    void outputbuttonclick();

    void font();

    void setDockSize(QDockWidget *, int, int);


private:

    QPushButton *rp,*ct,*exit,*tf,*oput,*modify,*start,*go,*step_spb,*break_bpb,*plot_graph1;

    QRadioButton *lru,*lfu,*random;

    QSpinBox *n,*k,*l,*memory_size,*step_s,*break_b;

    QComboBox *c1;

    QLabel *la1,*la2,*la3,*op1,*op2,*op3,*op4,*ip,*tfl,*memory_label,*start_label,*go_label,*simulation_controls,*step_sl,*break_bl;

    QMessageBox *m1,*m2,*m3;

    QWidget * widget1;

    QString *fn1,*fn2,*fn3,*output_file;

    QHBoxLayout *l16,*l11,*l12,*l13,*l14,*l17,*l15,*l19;

    QLineEdit *le,*le1;

    QDockWidget *dck,*drawing_docket1,*drawing_docket2;

    QMainWindow *window;

    enum {recentfiles = 5 };

    QAction *exitaction,*seperator,*action1,*recentfileaction[recentfiles],*about_qt,*convert;

    QMenu *filemenu,*helpmenu,*quit;

    QTextEdit *te;

    TRS *graphics1_ob;

    QDialog *qd1;

    QFont *fo;

    Plotting *graphics2_ob;



signals:



private slots:

    //invoked when Replacement Policy button clicked
    void RPmessagebox();

    //invoked when Cache button clicked
    void CTmessagebox();

    //invoked when Exit button clicked
    void windowclose();

    //invoked when Browse button clicked
    void openfilepath();

    //qmenu action Exit functionality
    void dockwidgetclose();

    //called when qmenu action New is clicked
    void create_dialogbox();

    //to check memory size M
    void check_valueset1();

    //when help->about_qt is clicked
    void help_qt();

    //called when open file button is clicked
    void read_file();

    //called when modify button is clicked
    void save_file();

    void convert_file();

    void convertandsave_file();

    void drawing_window();

    void qd1_close();

    void toggleView_sz(int);

    void toggleView_rs(int);

    void check_valueset2();

    void returnToOldMaxMinSizes();

};

#endif // DIALOG_H
