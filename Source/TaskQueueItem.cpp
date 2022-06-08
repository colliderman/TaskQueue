/*
  ==============================================================================

    TaskQueueItem.cpp
    Created: 7 Jun 2022 1:39:32pm
    Author:  Cody Gilchrist

  ==============================================================================
*/

#include "TaskQueueItem.h"

TaskQueueItem::TaskQueueItem (const ValueTree& v, UndoManager& um)
: tree (v), undoManager (um)
{
    tree.addListener (this);
}

String TaskQueueItem::getUniqueName() const
{
    return tree["name"].toString();
}

bool TaskQueueItem::mightContainSubItems()
{
    return tree.getNumChildren() > 0;
}

void TaskQueueItem::addChild(const ValueTree &childToAdd)
{
    tree.addChild(childToAdd, -1, &undoManager);
}

void TaskQueueItem::paintItem (Graphics& g, int width, int height)
{
    if (isSelected()) {
        g.fillAll(Colours::teal);
    }
    
    g.setColour(Colours::black);
    
    g.setFont (15.0f);
    
    g.drawText (tree["name"].toString(),
                4, 0, width - 4, height,
                Justification::centredLeft, true);
}

void TaskQueueItem::itemOpennessChanged (bool isNowOpen)
{
    if (isNowOpen && getNumSubItems() == 0)
        refreshSubItems();
    else
        clearSubItems();
}

var TaskQueueItem::getDragSourceDescription()
{
    return "Drag Demo";
}

bool TaskQueueItem::isInterestedInDragSource (const DragAndDropTarget::SourceDetails& dragSourceDetails)
{
    return dragSourceDetails.description == "Drag Demo";
}

void TaskQueueItem::itemDropped (const DragAndDropTarget::SourceDetails&, int insertIndex)
{
    OwnedArray<ValueTree> selectedTrees;
    getSelectedTreeViewItems (*getOwnerView(), selectedTrees);
    
    moveItems (*getOwnerView(), selectedTrees, tree, insertIndex, undoManager);
}

 void TaskQueueItem::moveItems (TreeView& treeView, const OwnedArray<ValueTree>& items,
                       ValueTree newParent, int insertIndex, UndoManager& undoManager)
{
    if (items.size() > 0)
    {
        std::unique_ptr<XmlElement> oldOpenness (treeView.getOpennessState (false));
        
        for (auto* v : items)
        {
            if (v->getParent().isValid() && newParent != *v && ! newParent.isAChildOf (*v))
            {
                if (v->getParent() == newParent && newParent.indexOf (*v) < insertIndex)
                    --insertIndex;
                
                v->getParent().removeChild (*v, &undoManager);
                newParent.addChild (*v, insertIndex, &undoManager);
            }
        }
        
        if (oldOpenness.get() != nullptr)
            treeView.restoreOpennessState (*oldOpenness, false);
    }
}

 void TaskQueueItem::getSelectedTreeViewItems (TreeView& treeView, OwnedArray<ValueTree>& items)
{
    auto numSelected = treeView.getNumSelectedItems();
    
    for (int i = 0; i < numSelected; ++i)
        if (auto* vti = dynamic_cast<TaskQueueItem*> (treeView.getSelectedItem (i)))
            items.add (new ValueTree (vti->tree));
}

void TaskQueueItem::refreshSubItems()
{
    clearSubItems();
    
    for (int i = 0; i < tree.getNumChildren(); ++i)
        addSubItem (new TaskQueueItem (tree.getChild (i), undoManager));
}

void TaskQueueItem::valueTreePropertyChanged (ValueTree&, const Identifier&)
{
    repaintItem();
}

void TaskQueueItem::valueTreeChildAdded (ValueTree& parentTree, ValueTree&)          { treeChildrenChanged (parentTree); }
void TaskQueueItem::valueTreeChildRemoved (ValueTree& parentTree, ValueTree&, int)   { treeChildrenChanged (parentTree); }
void TaskQueueItem::valueTreeChildOrderChanged (ValueTree& parentTree, int, int)     { treeChildrenChanged (parentTree); }
void TaskQueueItem::valueTreeParentChanged (ValueTree&)  {}

void TaskQueueItem::treeChildrenChanged (const ValueTree& parentTree)
{
    if (parentTree == tree)
    {
        refreshSubItems();
        treeHasChanged();
        setOpen (true);
    }
    }
