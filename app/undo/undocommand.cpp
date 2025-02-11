/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2021 Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#include "undocommand.h"

#include "core.h"

namespace olive {

MultiUndoCommand::MultiUndoCommand() :
  done_(false)
{
}

void MultiUndoCommand::redo()
{
  if (!done_) {
    for (auto it=children_.cbegin(); it!=children_.cend(); it++) {
      (*it)->redo_and_set_modified();
    }
    done_ = true;
  }
}

void MultiUndoCommand::undo()
{
  if (done_) {
    for (auto it=children_.crbegin(); it!=children_.crend(); it++) {
      (*it)->undo_and_set_modified();
    }
    done_ = false;
  }
}

UndoCommand::UndoCommand()
{
  prepared_ = false;
}

void UndoCommand::redo_and_set_modified()
{
  redo_now();

  project_ = GetRelevantProject();
  if (project_) {
    modified_ = project_->is_modified();
    project_->set_modified(true);
  }
}

void UndoCommand::undo_and_set_modified()
{
  undo_now();

  if (project_) {
    project_->set_modified(modified_);
  }
}

void UndoCommand::redo_now()
{
  if (!prepared_) {
    prepare();
    prepared_ = true;
  }

  redo();
}

void UndoCommand::undo_now()
{
  undo();
}

}
