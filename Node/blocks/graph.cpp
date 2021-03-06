#include "graph.h"

Graph::Graph(int i):
    BlockIO(i, 2, 0, BlockItem::BlockType::Graph)
{
    init();
}

void Graph::init()
{
    glWidget = new GLWidget();

    lblAxis0 = new QLabel("Input0");
    lblAxis1 = new QLabel("Input1");

    cbAxis0 = new QComboBox;
    cbAxis0->addItem("x");
    cbAxis0->addItem("y");
    cbAxis0->setCurrentIndex(0);

    cbAxis1 = new QComboBox;
    cbAxis1->addItem("x");
    cbAxis1->addItem("y");
    cbAxis1->setCurrentIndex(1);

    boxLayout->addWidget(lblAxis0);
    boxLayout->addWidget(cbAxis0);

    boxLayout->addWidget(lblAxis1);
    boxLayout->addWidget(cbAxis1);

    boxLayout->addWidget(glWidget, 4, 0, 1, 2);
    lblData->setVisible(false);
    teData->setVisible(false);

    boxLayout->rowStretch(1);

    groupBox->setLayout(boxLayout);
    groupBox->setTitle("Graph Block");
}

void Graph::generateCode(QString dir)
{

}


void Graph::draw(){
    int axis0 = 0;
    int axis1 = 1;

    if(cbAxis0->currentIndex() != cbAxis1->currentIndex())
    {
        axis0 = cbAxis0->currentIndex();
        axis1 = cbAxis1->currentIndex();
    }

    int size = getSize(0, 0);
    glWidget->create_array(size);
    for(int i = 0; i < size; i++)
    {
        if(axis0 == 0)
        {
            glWidget->set_array_val(i, in[0][i], in[1][i]);
        }
        else
        {
            glWidget->set_array_val(i, in[1][i], in[0][i]);
        }
    }
    glWidget->normalize_x_y();
    //glWidget->repaint();
    glWidget->update();
}

void Graph::resetGL(){
    glWidget->clearGL();

}

void Graph::setData(char *data)
{
    if(data == nullptr)
    {
        return;
    }
    qDebug() << "CREQATING GRAPH INS";
    //resetGL();
    //reset();
    Types type = Types::PACK_COUNT_MAX;
    size_t size_0 = 0, size_1 = 0;
    char *data_0 = nullptr, *data_1 = nullptr;

    getData(0, data, &type, &size_0, &data_0);
    getData(1, data, &type, &size_1, &data_1);
    qDebug() << "SIZE FROM GRAPH " << size_0 << " " << size_1 << endl;
    qDebug() << "type FROM GRAPH " << type << endl;
    createIOArray(0, 0, size_0);
    createIOArray(0, 1, size_1);
    size_t add = 0;
    if(type == Types::Pack_Int)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            int d;
            memcpy(&d, data_0 + add, sizeof (int));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (int);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            int d;
            memcpy(&d, data_1 + add, sizeof (int));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (int);
        }
    }
    else if(type == Types::Pack_Float)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            float d = 0;
            memcpy(&d, data_0 + i * sizeof (d), sizeof (d));
            in[0][i] = d;
            //qDebug() << i << " " << d << endl;
            flagIn[0] = true;
            add += sizeof (d);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            float d = 0;
            memcpy(&d, data_1 + add, sizeof (float));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (float);
        }
    }
    else if(type == Types::Pack_Double)
    {
        for(size_t i = 0; i < size_0; i++)
        {
            double d;
            memcpy(&d, data_0 + add, sizeof (double));
            in[0][i] = d;
            flagIn[0] = true;
            add += sizeof (double);
        }
        add = 0;
        for(size_t i = 0; i < size_1; i++)
        {
            double d;
            memcpy(&d, data_1 + add, sizeof (double));
            in[1][i] = d;
            flagIn[1] = true;
            add += sizeof (double);
        }
    }
    draw();
}

