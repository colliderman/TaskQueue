/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

/*
 TODO:
 
 - selecting a task should enable the add sub task button
 - need ability to select a task
 - need ability to edit a tasks name
 - need ability to mark task as completed
 - ability to show how many tasks are completed and how many remain on a task that has subtasks
 
 - save a task list to disk
 - open a task list from disk
 - create a new task list
 - show the tasks list's file name in the menu bar
 
 - auto save every 1s
 - app icon
 
 - ability to open a task list by double clicking the file name
 
 - adding a task should auto show the text editor for editing the name of the task
 - show the date/time task added
 - show the date/time task completed
 
 - remember window position/size when program is open/closed
 
 - add subtask should add a child to whatever node is selected
    - should do the same show editor thing
    - should automatically re-select parent task and deselct subtask
 
 - double click in blank area to add task
*/

//==============================================================================
MainComponent::MainComponent()
{
    addAndMakeVisible(taskQueueContainer);
    setSize (600, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
    taskQueueContainer.setBounds(getLocalBounds());
}
