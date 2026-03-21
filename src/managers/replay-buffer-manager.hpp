/**
 * @file replay-buffer-manager.hpp
 * @brief Manages replay buffer operations for the plugin
 * @author Joshua Potter
 * @copyright GPL v2 or later
 */

#pragma once

// OBS includes
#include <obs-module.h>
#include <obs-frontend-api.h>

// STL includes
#include <atomic>
#include <string>
#include <stdexcept>

// Qt includes
#include <QObject>
#include <QMessageBox>

namespace ReplayBufferPro
{
  /**
   * @brief Manages replay buffer operations including saving
   */
  class ReplayBufferManager : public QObject
  {
    Q_OBJECT

  public:
    //=========================================================================
    // CONSTRUCTORS & DESTRUCTOR
    //=========================================================================
    /**
     * @brief Constructor
     * @param parent Parent QObject
     */
    explicit ReplayBufferManager(QObject *parent = nullptr);

    /**
     * @brief Destructor
     */
    ~ReplayBufferManager() = default;

    //=========================================================================
    // REPLAY BUFFER OPERATIONS
    //=========================================================================
    /**
     * @brief Saves a segment of the replay buffer with specified duration
     * @param duration Seconds to save
     * @param parent Parent widget for error messages
     * @return Success status
     */
    bool saveSegment(int duration, QWidget *parent = nullptr);

    /**
     * @brief Saves the entire replay buffer
     * @param parent Parent widget for error messages
     * @return Success status
     */
    bool saveFullBuffer(QWidget *parent = nullptr);
  };

} // namespace ReplayBufferPro