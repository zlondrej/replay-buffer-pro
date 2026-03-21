/**
 * @file replay-buffer-manager.cpp
 * @brief Implementation of replay buffer management for the Replay Buffer Pro plugin
 */

#include "managers/replay-buffer-manager.hpp"
#include "managers/settings-manager.hpp"
#include "utils/logger.hpp"

// OBS includes
#include <util/platform.h>

// Qt includes
#include <QMessageBox>
#include <QString>

namespace ReplayBufferPro
{
  //=============================================================================
  // CONSTRUCTORS & DESTRUCTOR
  //=============================================================================

  ReplayBufferManager::ReplayBufferManager(QObject *parent)
      : QObject(parent)
  {
  }

  //=============================================================================
  // REPLAY BUFFER OPERATIONS
  //=============================================================================

  bool ReplayBufferManager::saveSegment(int duration, QWidget *parent)
  {
    if (!obs_frontend_replay_buffer_active())
    {
      if (parent)
      {
        QMessageBox::warning(parent, obs_module_text("Warning"),
                             obs_module_text("ReplayBufferNotActive"));
      }
      return false;
    }

    SettingsManager settingsManager;
    int currentBufferLength = settingsManager.getCurrentBufferLength();

    if (duration > currentBufferLength)
    {
      if (parent)
      {
        QMessageBox::warning(parent, obs_module_text("Warning"),
                             QString(obs_module_text("CannotSaveSegment"))
                                 .arg(duration)
                                 .arg(currentBufferLength));
      }
      return false;
    }

    // Call the OBS frontend API to save with duration-limiting
    obs_frontend_replay_buffer_save_duration(duration * 1000000LL);
    return true;
  }

  bool ReplayBufferManager::saveFullBuffer(QWidget *parent)
  {
    if (obs_frontend_replay_buffer_active())
    {
      obs_frontend_replay_buffer_save();
      return true;
    }
    else if (parent)
    {
      QMessageBox::warning(parent, obs_module_text("Error"),
                           obs_module_text("ReplayBufferNotActive"));
    }
    return false;
  }
}