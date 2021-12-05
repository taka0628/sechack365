#ifndef PASS_CHECK_H
#define PASS_CHECK_H

#include <QWidget>

namespace Ui {
class pass_check;
}

class pass_check : public QWidget {
    Q_OBJECT

public:
    explicit pass_check(QWidget* parent = 0);
    ~pass_check();

private:
    Ui::pass_check* ui;
};

#endif // PASS_CHECK_H
