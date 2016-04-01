#include <QCoreApplication>
#include <limits.h>
#include <gtest/gtest.h>
 
int main(int argc, char **argv) {
    //QCoreApplication needed for d-bus connections
    QCoreApplication app(argc, argv);

  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
