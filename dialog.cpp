//Madhusudhan Ramakrishnaiah - A04735682

#include "dialog.h"
#include "glwidget.h"
#include <math.h>
#include <cmath>
#include <functional>
#include <ploting.h>

//default constructor called when object of this class is created
ca::ca(QWidget *parent)
    : QDialog(parent){

    A=0.0,B=0.0,C=0.0,T=0.0;

    font();

    create_label();

    create_PushButton();

    create_radiobutton();

    create_spinbox();

    create_combobox();

    create_lineedit();

    create_layout();

    create_dockwidget();

    drawing_window();

    create_menu();

}

//creates menus file and help and adds actions
void ca::create_menu(){

    filemenu=new QMenu();
    filemenu=window->menuBar()->addMenu(tr("&File"));

    helpmenu=new QMenu();
    helpmenu=window->menuBar()->addMenu(tr("&Help"));

    create_menuactions();

    filemenu->addAction(action1);

    filemenu->addAction(convert);

    seperator=new QAction(this);
    seperator=filemenu->addSeparator();

    filemenu->addSeparator();

    filemenu->addAction(exitaction);

    helpmenu->addAction(about_qt);

}


//creates actions for adding to menus
void ca::create_menuactions(){

    action1=new QAction(tr("&New"),this);
    action1->setShortcut(tr("Alt+N"));
    action1->setStatusTip(tr("Create a new File"));
    connect(action1,SIGNAL(triggered()),this,SLOT(create_dialogbox()));

    exitaction=new QAction(tr("&Quit"),this);
    exitaction->setShortcut(tr("Alt+Q"));
    exitaction->setStatusTip(tr("Quit"));
    connect(exitaction,SIGNAL(triggered()),this,SLOT(windowclose()));

    about_qt=new QAction(tr("&About QT"),this);
    about_qt->setStatusTip(tr("Regarding Qt"));
    connect(about_qt,SIGNAL(triggered()),this,SLOT(help_qt()));

    convert=new QAction(tr("&Convert"),this);
    connect(convert,SIGNAL(triggered()),this,SLOT(convert_file()));

}

//new dialog box is created when new action is selected from file menu
void ca::create_dialogbox(){

   QDialog *db=new QDialog(this);
   db->setWindowTitle("Open Existing File");

   QPushButton *openfile=new QPushButton("open file");
   openfile->setFont(*fo);
   openfile->setFixedSize(90,40);
   connect(openfile,SIGNAL(clicked()),this,SLOT(read_file()));

   //creates text browser to read file into and display user
   te=new QTextEdit();

   QHBoxLayout *hbox1=new QHBoxLayout();
   hbox1->addWidget(openfile);

   QHBoxLayout *hbox2=new QHBoxLayout();
   hbox2->addWidget(te);
   te->setFixedWidth(900);
   te->setFixedHeight(500);

   modify=new QPushButton("Save");
   modify->setFont(*fo);
   modify->setFixedSize(90,40);
   QHBoxLayout *hbox3=new QHBoxLayout();
   hbox3->addWidget(modify);

   QVBoxLayout *vbox=new QVBoxLayout();
   vbox->addLayout(hbox1);
   vbox->addLayout(hbox2);
   vbox->addLayout(hbox3);

   db->setLayout(vbox);
   db->setStyleSheet("background-color:white;");
   db->show();

}

//opens and reads the file contents into text edit
void ca::read_file()
{
  QString fileName = QFileDialog::getOpenFileName(this, tr("Select a file"), "", tr("Text Files (*.txt);;c++ source files (*.cpp);;All Files (*.*)"));
  if(fileName!="")
    {
      QFile fIn(fileName);
      if(!fIn.open(QIODevice::ReadOnly))
        {
          QMessageBox::critical(this, tr("Error"), tr("File could not opened"));
          return;
        }
        QTextStream in(&fIn);
        te->setText(in.readAll());
         connect(modify,SIGNAL(clicked()),this,SLOT(save_file()));
        fIn.close();
    }
  else
  {
    QMessageBox confirm;
    confirm.setText(tr("No file has been selected"));
    confirm.setStandardButtons(QMessageBox::Ok);
    confirm.setDefaultButton(QMessageBox::Ok);

    if(confirm.exec()==QMessageBox::Retry)
    {
      open();
    }
  }
}

//saves the file modified
void ca::save_file()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("Text Files (*.txt);;C++ Source Files (*.cpp);;All files(*.*)"));
  QFile fOut(fileName);
  if(fileName!="")
  {
    if(fOut.open(QIODevice::WriteOnly))
    {
      QTextStream out(&fOut);
      out<<te->toPlainText();
      out.flush();
      fOut.close();
    }
    else
    {
      QMessageBox::critical(this, tr("Error"), tr("File could not be saved"));
      return;
    }
  }
}


//creates a dockwidget and adds all the other child widgets to it
void ca::create_dockwidget(){

   //creates a dock widget,adds all widgets to it
   dck=new QDockWidget();
   //disbales the movable,closable,floatable feature of dcoket widget
   //dck->setFeatures(0*00);

   dck->setWidget(widget1);
   dck->setWindowTitle("Cache Parameters");
   dck->setStyleSheet("background-color: white;");
   //setDockSize(dck,400,400);


   //creates main window object and adds the dock widget to it
   window=new QMainWindow();
   window->addDockWidget(Qt::LeftDockWidgetArea,dck);
   window->setWindowTitle("Cache System Simulation");
   window->show();

}

//for creating line edits
void ca::create_lineedit(){

    //line edit to display the file path selected from user
    le=new QLineEdit();
    le->setFont(*fo);

}

//creates new dialog box displaying the outputs
void ca::outputbuttonclick(){

    QDialog *qd=new QDialog();
    qd->setWindowTitle("Cache System Output");

    //creating label+lcd number display for displaying outputs
    QLabel *ql1=new QLabel();
    ql1->setFont(*fo);
    ql1->setText("<b>Number of Memory Access Instances:</b>");
    QLCDNumber *lcd1=new QLCDNumber();
    lcd1->display(10);

    QLabel *ql2=new QLabel("<b>Hit Ratio:</b>");
    ql2->setFont(*fo);
    QLCDNumber *lcd2=new QLCDNumber();
    lcd2->display(20);

    QLabel *ql3=new QLabel("<b>Compulsory Miss Ratio:</b>");
    ql3->setFont(*fo);
    QLCDNumber *lcd3=new QLCDNumber();
    lcd3->display(30);

    QLabel *ql4=new QLabel("<b>Miss Ratio:</b>");
    ql4->setFont(*fo);
    QLCDNumber *lcd4=new QLCDNumber();
    lcd4->display(40);

    //output for 4 integers based on m,k,n
    A=ceil(log2(memory_size->value()));
    B=ceil(log2(k->value()));
    C=ceil((log2(n->value())));
    T=A-B-C;

    QLabel *ql5=new QLabel("<b>The size of a reference word in bits - (A):</b> ");
    ql5->setFont(*fo);
    QLCDNumber *lcd5=new QLCDNumber();
    lcd5->display(A);

    QLabel *ql6=new QLabel("<b>The size of the offset field in bits - (B):</b> ");
    ql6->setFont(*fo);
    QLCDNumber *lcd6=new QLCDNumber();
    lcd6->display(B);

    QLabel *ql7=new QLabel("<b>The size of the index field in bits - (C):</b> ");
    ql7->setFont(*fo);
    QLCDNumber *lcd7=new QLCDNumber();
    lcd7->display(C);

    QLabel *ql8=new QLabel("<b>The size of the tag field in bits - (T):</b>");
    ql8->setFont(*fo);
    QLCDNumber *lcd8=new QLCDNumber();
    lcd8->display(T);

    QFrame *hline4 = new QFrame();
    hline4->setFrameShape(QFrame::HLine);
    hline4->setFrameShadow(QFrame::Sunken);

    QGridLayout *grid2=new QGridLayout;

    grid2->addWidget(ql1,0,0,1,1);
    grid2->addWidget(lcd1,0,1,1,4);

    grid2->addWidget(ql2,1,0,1,1);
    grid2->addWidget(lcd2,1,1,1,4);

    grid2->addWidget(ql3,2,0,1,1);
    grid2->addWidget(lcd3,2,1,1,4);

    grid2->addWidget(ql4,3,0,1,1);
    grid2->addWidget(lcd4,3,1,1,4);

    grid2->addWidget(hline4,4,0,1,5);

    grid2->addWidget(ql5,5,0,1,1);
    grid2->addWidget(lcd5,5,1,1,4);

    grid2->addWidget(ql6,6,0,1,1);
    grid2->addWidget(lcd6,6,1,1,4);

    grid2->addWidget(ql7,7,0,1,1);
    grid2->addWidget(lcd7,7,1,1,4);

    grid2->addWidget(ql8,8,0,1,1);
    grid2->addWidget(lcd8,8,1,1,4);

    qd->setLayout(grid2);
    qd->setStyleSheet("background-color: white;");
    qd->show();
}

//dialog box for replacement policy button
void ca::RPmessagebox(){

    //message box pop up when replacement policy button is clicked
    m1=new QMessageBox();
    m1->setWindowTitle("About Relacement Policies");
    m1->setText("Brief Description about the 3 Rreplacement Policies");
    m1->setInformativeText("LFU: Counts how often an item is needed.Those that are used least often are discarded first.\n\nLRU: Discards the least recently used items first.This algorithm requires keeping track of what was used recently\n\nRandom: Here it randomly selects a candidate item and discards it to make space when necessary.This algorithm does not require keeping any information about the access history");
    m1->setStyleSheet("background-color:white");
    m1->exec();

}

//dialog box for cache types button
void ca::CTmessagebox(){

    //message box pop up when cache push button is clicked
    m2=new QMessageBox();
    m2->setWindowTitle("About Cache Types");
    m2->setText("Brief Description about the 2 Cache Types");
    m2->setInformativeText("Most modern desktop and server CPUs have at least three independent caches out of which\n\nInstruction Cache is used to speed up executable instruction fetch\n\nData Cache is used to speed up data fetch and store");
    m2->setStyleSheet("background-color:white");
    m2->exec();

}

//for creating qlabel
void ca::create_label(){

    //creates labels
    la1=new QLabel("Select Number of sets:");
    la1->setFont(*fo);

    la2=new QLabel("Select Number of ways:");
    la2->setFont(*fo);

    la3=new QLabel("Select Number of bytes per block:");
    la3->setFont(*fo);

    tfl=new QLabel("Select Trace File:");
    tfl->setFont(*fo);

    memory_label=new QLabel("Select Memory Size:");
    memory_label->setFont(*fo);

    simulation_controls=new QLabel("Simulation Controls:");
    simulation_controls->setFont(*fo);

    step_sl=new QLabel("     Select the trace element where to start from:");
    step_sl->setFont(*fo);

    break_bl=new QLabel("     Select the trace element where to break:");
    break_bl->setFont(*fo);

    start_label=new QLabel("     Select Start:");
    start_label->setFont(*fo);

    go_label=new QLabel("     Select Go:");
    go_label->setFont(*fo);

}

//for creating drop-down menus
void ca::create_combobox(){

    //cerates string consisting of the options provided in combo box
    QStringList s2;
    s2<<"None"<<"Instruction Cache"<<"Data Cache";

    //cretates combo box and adds options
    c1=new QComboBox();
    c1->setFont(*fo);
    c1->insertItems(0,s2);
    c1->setFixedSize(170,30);

}

//for creating push buttons
void ca::create_PushButton(){

    //button for Replacement policy
    rp=new QPushButton ("Replacement policy");
    rp->setFont(*fo);
    rp->setFixedSize(200,40);
    rp->setToolTip("Click for Info");
    connect(rp,SIGNAL(clicked()),this,SLOT(RPmessagebox()));

    //button for Cache types
    ct=new QPushButton("Cache type");
    ct->setFont(*fo);
    ct->setFixedSize(200,40);
    ct->setToolTip("Click for Info");
    connect(ct,SIGNAL(clicked()),this,SLOT(CTmessagebox()));

    //button for implementing exit functionality
    exit=new QPushButton("Exit");
    exit->setFont(*fo);
    connect(exit,SIGNAL(clicked()),this,SLOT(windowclose()));
    exit->setFixedSize(90,40);
    exit->move(10,10);

    //button to browse the files from the local directory
    tf=new QPushButton("Browse");
    tf->setFont(*fo);
    tf->setToolTip("Choose File Path");
    connect(tf,SIGNAL(clicked()),this,SLOT(openfilepath()));

    //button for Output to view the cache output
    oput=new QPushButton("Output");
    oput->setFont(*fo);
    oput->setToolTip("Click to view");
    connect(oput,SIGNAL(clicked()),this,SLOT(check_valueset1()));

    //Simulation Controls
    //button for start
    start=new QPushButton("Start");
    start->setFont(*fo);
    start->setToolTip("Click to view");

    //button for go
    go=new QPushButton("Go");
    go->setFont(*fo);
    go->setToolTip("Click to view");

    step_spb=new QPushButton("Step_s");
    step_spb->setFont(*fo);

    break_bpb=new QPushButton("Break_b");
    break_bpb->setFont(*fo);

    //button for Plotting graph
    plot_graph1=new QPushButton("Plot");
    plot_graph1->setFont(*fo);
    plot_graph1->setFixedSize(90,40);
    plot_graph1->setToolTip("Click to view");
    connect(plot_graph1,SIGNAL(clicked()),this,SLOT(check_valueset2()));

}

//for creating radio buttons
void ca::create_radiobutton(){

     //Creates radio buttons for replacement policies
     lru=new QRadioButton("Least Recently Used");
     lru->setFont(*fo);

     lfu=new QRadioButton("Least Frequently Used");
     lfu->setFont(*fo);

     random=new QRadioButton("Random");
     random->setFont(*fo);

}

//for creating layout
void ca::create_layout(){

    //frame for horizontal line
    QFrame *hline1 = new QFrame();
    hline1->setFrameShape(QFrame::HLine);
    hline1->setFrameShadow(QFrame::Sunken);

    QFrame *hline2 = new QFrame();
    hline2->setFrameShape(QFrame::HLine);
    hline2->setFrameShadow(QFrame::Raised);

    QFrame *hline3 = new QFrame();
    hline3->setFrameShape(QFrame::HLine);
    hline3->setFrameShadow(QFrame::Raised);

    //frame for vertical line
    QFrame *vline1= new QFrame();
    vline1->setFrameShape(QFrame::Panel);
    vline1->setFrameShadow(QFrame::Plain);

    QGridLayout *grid1_layout=new QGridLayout;

    grid1_layout->addWidget(rp,0,0,1,1);
    grid1_layout->addWidget(lru,1,0,1,1);
    grid1_layout->addWidget(lfu,2,0,1,1);
    grid1_layout->addWidget(random,3,0,1,1);

    grid1_layout->addWidget(ct,4,0,1,1);
    grid1_layout->addWidget(c1,4,1,1,1);

    grid1_layout->addWidget(tfl,6,0,1,1);
    grid1_layout->addWidget(le,7,0,1,1);
    grid1_layout->addWidget(tf,7,1,1,1);

    grid1_layout->addWidget(hline1,8,0,1,5);

    grid1_layout->addWidget(la2,9,0,1,1);
    grid1_layout->addWidget(l,9,1,1,1);

    grid1_layout->addWidget(la1,10,0,1,1);
    grid1_layout->addWidget(n,10,1,1,1);

    grid1_layout->addWidget(la3,11,0,1,1);
    grid1_layout->addWidget(k,11,1,1,1);

    grid1_layout->addWidget(memory_label,12,0,1,1);
    grid1_layout->addWidget(memory_size,12,1,1,1);

    grid1_layout->addWidget(hline2,13,0,1,5);

    grid1_layout->addWidget(simulation_controls,14,0,1,1);

    grid1_layout->addWidget(simulation_controls,14,0,1,1);
    grid1_layout->addWidget(step_sl,15,0,1,1);
    grid1_layout->addWidget(step_s,15,1,1,1);

    grid1_layout->addWidget(break_bl,16,0,1,1);
    grid1_layout->addWidget(break_b,16,1,1,1);

    QHBoxLayout *sc=new QHBoxLayout;
    sc->addWidget(start);
    sc->addWidget(go);
    sc->addWidget(step_spb);
    sc->addWidget(break_bpb);

    grid1_layout->addLayout(sc,17,0,1,5);

    grid1_layout->addWidget(hline3,18,0,1,5);

    //adding output,exit push button
    QHBoxLayout *oputlayout=new QHBoxLayout();
    oputlayout->addWidget(oput);
    oput->setFixedSize(90,40);
    oputlayout->addWidget(exit);
    //oputlayout->addWidget(plot_graph1);

    grid1_layout->addLayout(oputlayout,19,0,1,5);

    //creating window widget and populating them with other layouts
    widget1 = new QWidget;
    QString s="Simulation of Cache System";
    widget1->setWindowTitle(s);
    widget1->setLayout(grid1_layout);
    widget1->setStyleSheet("background-color: white;");

}

//when Quit button is pressed
void ca::windowclose(){

    window->close();
}

//when Exit is selected
void ca::dockwidgetclose(){

    dck->close();
}

//for user to select the files from directories
void ca::openfilepath(){

    //cretaing string to hold the file path selected by user
    fn1=new QString();

    //to get file path and allows user to select file format of all files only
    *fn1=QFileDialog::getOpenFileName(this,tr("Open File"),"C://","All Files (*.*);;text file (.*txt)");

    //sets the line edit with the file path selected by user
    le->setText(*fn1);

}

//creates spin boxes
void ca::create_spinbox(){

     //creates spin box for no.of sets
     n = new QSpinBox();
     n->setFont(*fo);
     n->setRange(1,16);

     //creates spin box for no.of ways
     l = new QSpinBox();
     l->setFont(*fo);
     l->setRange(1,16);

     //creates spin box for no.of bytes per block
     k = new QSpinBox();
     k-> setFont(*fo);
     k->setRange(4,1024);

     //for memory_size input
     memory_size=new QSpinBox();
     memory_size->setFont(*fo);
     memory_size->setRange(256,268435456);

     //for step_s input
     step_s=new QSpinBox();
     step_s->setFont(*fo);
     step_s->setRange(1,10);

     //for break_b input
     break_b=new QSpinBox();
     break_b->setFont(*fo);
     break_b->setRange(1,10);

}

//validates the values of memory,no.of bytes per block set by user
void ca::check_valueset1(){

    //using bitwise binary operator to check whether memory_size value is a power of 2
    ulong x=memory_size->value();
    bool v=((x != 0) && ((x & (x - 1))));

    if((k->value()%2)!=0){
        QMessageBox *k_messagebox=new QMessageBox(this);
        k_messagebox->warning(this,"Memory Size Wrong","Please Set no.of bytes per block to even",QMessageBox::Ok|QMessageBox::Default);
        k_messagebox->setStyleSheet("background-color:white;");

    }

    if(v!=0){
        QMessageBox *memory_messagebox=new QMessageBox(this);
        memory_messagebox->warning(this,"Memory Size Wrong","Please Set Memory to the Power of 2",QMessageBox::Ok|QMessageBox::Default);
        memory_messagebox->setStyleSheet("background-color:white;");
    }


    else if(((k->value()%2)==0)&&(memory_size->value()%2==0)){
        outputbuttonclick();
    }


}


//create a message box and pops up when user selects the Help->About QT
void ca::help_qt(){

        QMessageBox *qt_messagebox=new QMessageBox(this);
        qt_messagebox->information(this,"QT information"
                                       ,"Qt Creator is a cross-platform C++, JavaScript and QML integrated development environment which is part of the SDK for the Qt GUI Application development framework.[3] It includes a visual debugger and an integrated GUI layout and forms designer. The editor's features include syntax highlighting and autocompletion. Qt Creator uses the C++ compiler from the GNU Compiler Collection on Linux and FreeBSD. On Windows it can use MinGW or MSVC with the default install and can also use Microsoft Console Debugger when compiled from source code. Clang is also supported."
                                       ,QMessageBox::Ok|QMessageBox::Default);
        qt_messagebox->setStyleSheet(" background-color : white;");


}

//prepends 0x string to each line of the dile selected by user and saves it in a particular path
void ca::convertandsave_file(){

    QFile input_file(*fn3);

    //new file for storing the converted file data
    QFile output_file;
    output_file.setFileName("/home/user/Desktop/Gui/ca/output.txt");
    output_file.open(QIODevice::ReadWrite );

    //stream to write data into output file
    QTextStream output_stream(&output_file);

    if (!input_file.open(QIODevice::ReadWrite | QIODevice::Text))
        return;

    else{

        //stream to read data from input file
        QTextStream input_stream(&input_file);
        QString input_string,output_string;

        //reads until the end of input file
        while(!input_stream.atEnd()){

            //reads each line form ip file and prepends 0x to each line
            input_string=input_stream.readLine();
            output_string="0x"+input_string;
            output_stream<<output_string<<"\n";
        }
    }

    input_file.close();
    output_file.close();

}


//asks the user to select file path
void ca::convert_file(){

    qd1=new QDialog();
    qd1->resize(390,340);


    //cretaing string to hold the file path selected by user
    fn3=new QString();

    //to get file path and allows user to select file format of all files only
    *fn3=QFileDialog::getOpenFileName(this,tr("Open File"),"C://","All Files (*.*);;text file (.*txt)");

    //sets the line edit with the file path selected by user
    le1=new QLineEdit;
    le1->setFont(*fo);
    le1->setText(*fn3);

    //push button for convert
    QPushButton *convert_pb=new QPushButton("Convert");
    convert_pb->setFont(*fo);
    connect(convert_pb,SIGNAL(clicked()),this,SLOT(convertandsave_file()));
    connect(convert_pb,SIGNAL(clicked()),this,SLOT(qd1_close()));

    QGridLayout *grid2=new QGridLayout;

    grid2->addWidget(le1,0,0,1,1);

    grid2->addWidget(convert_pb,2,0,1,1);

    qd1->setLayout(grid2);

    qd1->show();

}

//creates a new docket widget,adds the drawing widget to it
void ca::drawing_window(){

    //creates a dock widget,adds all widgets to it
   drawing_docket1=new QDockWidget();
   drawing_docket1->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

   //disbales the movable,closable,floatable feature of dcoket widget
   //drawing_docke1t->setFeatures(0*00);

   drawing_docket1->setWindowTitle("Graphics Window -1");
   drawing_docket1->setStyleSheet("background-color: white;");

   //creates new object of glwidget and adds this to the docket widget
   graphics1_ob=new TRS();

   //rotation control widget
   QGroupBox *gbox = new QGroupBox( drawing_docket1);
   QLabel *label_rs = new QLabel(drawing_docket1);
   label_rs->setText("<b>Rotation Control:</b>");

   QDial *dial_rs = new QDial(drawing_docket1);
   dial_rs->setPalette(Qt::green);

   QLCDNumber *lcd_rs = new QLCDNumber(drawing_docket1);

   //size
   QLabel *label_sz = new QLabel(drawing_docket1);
   label_sz->setText("Scaling Control");

   QSlider *slider_sz = new QSlider(drawing_docket1);
   slider_sz->setOrientation(Qt::Horizontal);
   slider_sz->setRange(0,20);
   slider_sz->setPalette(Qt::green);

   QLCDNumber *lcd_sz = new QLCDNumber(drawing_docket1);

   //creating layout for the above dock1 widgets
   QGridLayout *grid1 = new QGridLayout;
   grid1->addWidget(label_rs,0,0,1,1);
   grid1->addWidget(dial_rs,0,1,1,1);
   grid1->addWidget(lcd_rs,0,2,1,1);

   grid1->addWidget(label_sz,1,0,1,1);
   grid1->addWidget(slider_sz,1,1,1,1);
   grid1->addWidget(lcd_sz,1,2,1,1);

   grid1->addWidget(graphics1_ob,2,0,3,3);

   connect(slider_sz,SIGNAL(valueChanged(int)),lcd_sz,SLOT(display(int)));
   connect(slider_sz,SIGNAL(valueChanged(int)),this,SLOT(toggleView_sz(int)));

   connect(dial_rs,SIGNAL(valueChanged(int)),lcd_rs,SLOT(display(int)));
   connect(dial_rs,SIGNAL(valueChanged(int)),this,SLOT(toggleView_rs(int)));

   gbox->setLayout(grid1);

   drawing_docket1->setWidget(gbox);
   setDockSize(drawing_docket1,400,400);

   //adds docket to the right end of window
   window->addDockWidget(Qt::RightDockWidgetArea,drawing_docket1);

   //FOR WINDOW-2
   drawing_docket2=new QDockWidget();
   drawing_docket2->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea|Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);

   drawing_docket2->setWindowTitle("Graphics Window -2");
   drawing_docket2->setStyleSheet("background-color: white;");

   graphics2_ob = new Plotting(this,5.0,2.0,1.0);

   drawing_docket2->setWidget(graphics2_ob);

   setDockSize(drawing_docket2,400,600);

   //adds docket to the right end of window
   window->addDockWidget(Qt::RightDockWidgetArea,drawing_docket2);

   window->splitDockWidget(drawing_docket1,drawing_docket2,Qt::Horizontal);

}

//for scaling
void ca::toggleView_sz(int val){

    graphics1_ob->scaling_ob(val);
}

//for rotating
void ca::toggleView_rs(int val){

    graphics1_ob->rotating_ob(val);

}

//pops a message box giving file info
void ca::qd1_close(){
    qd1->close();
    QMessageBox::information(qd1,
                             "Converted file info",
                             "File Name: output.txt\nPath: /home/user/Desktop/Gui/ca/output.txt");

}

//to set font and its size in the whole app
void ca::font(){
    fo=new QFont("Arial",12,QFont::Bold);

}

//validates the values of memory,no.of bytes per block set by user
void ca::check_valueset2(){

    //using bitwise binary operator to check whether memory_size value is a power of 2
    ulong x=memory_size->value();
    bool v=((x != 0) && ((x & (x - 1))));

    if((k->value()%2)!=0){
        QMessageBox *k_messagebox=new QMessageBox(this);
        k_messagebox->warning(this,"Memory Size Wrong","Please Set no.of bytes per block to even",QMessageBox::Ok|QMessageBox::Default);
        k_messagebox->setStyleSheet("background-color:white;");
    }

    if(v!=0){
        QMessageBox *memory_messagebox=new QMessageBox(this);
        memory_messagebox->warning(this,"Memory Size Wrong","Please Set Memory to the Power of 2",QMessageBox::Ok|QMessageBox::Default);
        memory_messagebox->setStyleSheet("background-color:white;");
    }

    else if(((k->value()%2)==0)&&(memory_size->value()%2==0)){

    }

}




//global variable used for resizing dock widgets
QSize oldMaxSize, oldMinSize;

//to resize the dock widgets
void ca::setDockSize(QDockWidget* dock, int setWidth,int setHeight)
{

    oldMaxSize=dock->maximumSize();
    oldMinSize=dock->minimumSize();

  if (setWidth>=0){
      if (dock->width()<setWidth)
          dock->setMinimumWidth(setWidth);
      else dock->setMaximumWidth(setWidth);
  }

  if (setHeight>=0){
      if (dock->height()<setHeight)
          dock->setMinimumHeight(setHeight);
      else dock->setMaximumHeight(setHeight);
  }

  QTimer::singleShot(1, this, SLOT(returnToOldMaxMinSizes()));

}

void ca::returnToOldMaxMinSizes()
{
    this->setMinimumSize(oldMinSize);
    this->setMaximumSize(oldMaxSize);
}
