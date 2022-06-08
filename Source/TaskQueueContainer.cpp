/*
  ==============================================================================

    TaskQueueContainer.cpp
    Created: 7 Jun 2022 1:39:55pm
    Author:  Cody Gilchrist

  ==============================================================================
*/

#include "TaskQueueContainer.h"
#include "TaskQueueItem.h"

TaskQueueContainer::TaskQueueContainer()
{
    addAndMakeVisible (tree);
    addAndMakeVisible(addTaskButton);
    addAndMakeVisible(addSubTaskButton);
    
    tree.setDefaultOpenness (true);
    tree.setMultiSelectEnabled (true);
    rootItem.reset (new TaskQueueItem (createRootValueTree(), undoManager));
    tree.setRootItem (rootItem.get());
    
    startTimer (500);
    
    addTaskButton.onClick = [this]()
    {
        static int counter = 0;
        ValueTree task {"task"};
        task.setProperty("name", "task " + (String)counter++, &undoManager);
        
        rootItem->addChild(task);
    };
    
    setSize (500, 500);
}

TaskQueueContainer::~TaskQueueContainer()
{
    stopTimer();
    tree.setRootItem (nullptr);
}

void TaskQueueContainer::paint (Graphics& g)
{
    g.fillAll(Colours::white);
    
}

void TaskQueueContainer::resized()
{
//    auto r = getLocalBounds().reduced (8);
//
//    tree.setBounds (r);
    auto bounds = getLocalBounds();
    
    tree.setBounds(bounds.removeFromTop(getHeight() * 0.9));
    
    FlexBox fb;
    fb.flexDirection = FlexBox::Direction::row;
    fb.alignItems = FlexBox::AlignItems::stretch;
    
    fb.items.add(FlexItem(addTaskButton).withFlex(1));
    fb.items.add(FlexItem(addSubTaskButton).withFlex(1));
    
    fb.performLayout(bounds);
}



ValueTree TaskQueueContainer::createRootValueTree()
{
    auto vt = createTree ("Task Queue Tree");
    return vt;
}

ValueTree TaskQueueContainer::createTree (const String& desc)
{
    ValueTree t ("Item");
    t.setProperty ("name", desc, nullptr);
    return t;
}
//TreeView tree;
//
//std::unique_ptr<TaskQueueItem> rootItem;
//UndoManager undoManager;

void TaskQueueContainer::timerCallback()
{
    undoManager.beginNewTransaction();
}
