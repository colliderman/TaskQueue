/*
  ==============================================================================

    TaskQueueContainer.h
    Created: 7 Jun 2022 1:39:55pm
    Author:  Cody Gilchrist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

struct TaskQueueItem;
//==============================================================================
class TaskQueueContainer   : public Component,
public DragAndDropContainer,
private Timer
{
public:
    TaskQueueContainer();
    
    ~TaskQueueContainer() override;
    
    void paint (Graphics& g) override;
    
    void resized() override;
    
    
    
    ValueTree createRootValueTree();
    
private:
    ValueTree createTree (const String& desc);
    TreeView tree;
    
    std::unique_ptr<TaskQueueItem> rootItem;
    UndoManager undoManager;
    
    void timerCallback() override;
    TextButton addTaskButton {"Add Task"};
    TextButton addSubTaskButton {"Add SubTask"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaskQueueContainer)
};
