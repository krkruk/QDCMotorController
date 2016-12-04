#ifndef QDCMODELINTERFACE_H
#define QDCMODELINTERFACE_H


class QDCModelInterface
{
public:
    virtual void updateData(QByteArray data) = 0;
};

#endif // QDCMODELINTERFACE_H
