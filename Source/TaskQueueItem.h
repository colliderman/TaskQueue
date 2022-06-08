/*
  ==============================================================================

    TaskQueueItem.h
    Created: 7 Jun 2022 1:39:32pm
    Author:  Cody Gilchrist

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 This component lives inside our window, and this is where you should put all
 your controls and content.
 */

class TaskQueueItem  : public TreeViewItem,
private ValueTree::Listener
{
public:
    TaskQueueItem (const ValueTree& v, UndoManager& um);
    
    String getUniqueName() const override;
    
    bool mightContainSubItems() override;
    
    void addChild (const ValueTree& childToAdd);
    
    void paintItem (Graphics& g, int width, int height) override;
    
    void itemOpennessChanged (bool isNowOpen) override;
    
    var getDragSourceDescription() override;
    
    bool isInterestedInDragSource (const DragAndDropTarget::SourceDetails& dragSourceDetails) override;
    
    void itemDropped (const DragAndDropTarget::SourceDetails&, int insertIndex) override;
    
    static void moveItems (TreeView& treeView, const OwnedArray<ValueTree>& items,
                           ValueTree newParent, int insertIndex, UndoManager& undoManager);
    
    static void getSelectedTreeViewItems (TreeView& treeView, OwnedArray<ValueTree>& items);
    
private:
    ValueTree tree;
    UndoManager& undoManager;
    
    void refreshSubItems();
    
    void valueTreePropertyChanged (ValueTree&, const Identifier&) override;

    void valueTreeChildAdded (ValueTree& parentTree, ValueTree&) override;
    void valueTreeChildRemoved (ValueTree& parentTree, ValueTree&, int) override;
    void valueTreeChildOrderChanged (ValueTree& parentTree, int, int) override;
    void valueTreeParentChanged (ValueTree&) override;
    
    void treeChildrenChanged (const ValueTree& parentTree);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TaskQueueItem)
};
