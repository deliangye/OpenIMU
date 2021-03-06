#include "TestPipeline.h"

#include "../applicationOpenimu/app/core/components/Block.h"
#include "../applicationOpenimu/app/core/components/InputNode.h"
#include "../applicationOpenimu/app/core/components/OutputNode.h"
#include "../applicationOpenimu/app/core/json/json/json.h"
#include "../applicationOpenimu/app/core/Caneva.h"
#include <string>
#include <vector>
#include <QtGlobal>

TestPipeline::TestPipeline(QObject *parent) : QObject(parent)
{
    caneva = new Caneva("../savefiles/test_block_mul.json",0);
}

void TestPipeline::testsJSON()
{
    QFETCH(std::vector<float> , input1);
    QFETCH(std::vector<float> , input2);
    QFETCH(std::vector<float> , result);

    caneva->getBlock("multiplier")->GetInput<float>("input1")->Put(input1);
    caneva->getBlock("multiplier")->GetInput<float>("input2")->Put(input2);
    std::vector<float> calculated = caneva->getBlock("multiplier")->GetOutput<float>("output1")->getValueBuf();

    unsigned int minSize = std::min(std::min(input1.size(),input2.size()), calculated.size());
    for(int i = 0; i<minSize; i++)
        qFuzzyCompare(calculated[i],result[i]);
}

void TestPipeline::testsJSON_data()
{
    QTest::addColumn<std::vector<float> >("input1");
    QTest::addColumn<std::vector<float> >("input2");
    QTest::addColumn<std::vector<float> >("result");

    QTest::newRow("1") << std::vector<float>({1.1f,2.2f,3.3f}) // input1
                       << std::vector<float>({1.1f,2.2f,3.3f}) // input2
                       << std::vector<float>({1.21f,4.84f,10.89f}); // output

    QTest::newRow("2") << std::vector<float>({-1.1f,-2.2f,-3.3f}) // input1
                       << std::vector<float>({1.1f,2.2f,3.3f}) // input2
                       << std::vector<float>({-1.21f,-4.84f,-10.89f}); // output

    QTest::newRow("3") << std::vector<float>({-1.1f,-2.2f,-3.3f}) // input1
                       << std::vector<float>({-1.1f,-2.2f,-3.3f}) // input2
                       << std::vector<float>({1.21f,4.84f,10.89f}); // output


    QTest::newRow("4") << std::vector<float>({1.0f,2.0f,3.0f}) // input1
                       << std::vector<float>({0.0f,0.0f,0.0f}) // input2
                       << std::vector<float>({0.0f,0.0f,0.0f}); // output
}
