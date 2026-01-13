#include "SinkSub.h"

SinkSub::SinkSub(int winWidth, int winHeight) : winWidth_(winWidth), winHeight_(winHeight),
                                                shipTex_(LoadTexture("sprites/Ships_Sprite.png")),
                                                shipTexExpl_(LoadTexture("sprites/Ship_Explosion_Sprite.png")),
                                                subTex_(LoadTexture("sprites/Submarine_Sprite.png")),
                                                subTexExpl_(LoadTexture("sprites/Sub_Explosion_Sprite.png")),
                                                bombTex_(LoadTexture("sprites/Bomb_tile.png")),
                                                mineTex_(LoadTexture("sprites/Mine.png")),
                                                explTex_(LoadTexture("sprites/Explosion_Sprite.png")),
                                                splashTex_(LoadTexture("sprites/Splash_Sprite.png")),
                                                seagullTex_(LoadTexture("sprites/SeaGull_Sprite.png")),
                                                cloudTex_(LoadTexture("sprites/Cloud_Sprite.png")),
                                                iconTex_(LoadTexture("sprites/Icons.png")),
                                                GameOverTex_(LoadTexture("sprites/LifeBuoy.png"))

{
      // Корабль

      ship_ = new Destroyer(&shipTex_, &shipTexExpl_, 0.f, 150.f);

      ship_->SetVelocityStep(0.5);
      ship_->SetDefaultPos(winWidth_ / 2 - ship_->GetShipWidth() / 2, 150.f);
      ship_->SetToDefaultPos();
      ship_->SetBorders_X(0.f, static_cast<float>(winWidth_ - ship_->GetShipWidth()));

      // Море
      seaBeginY_ = static_cast<int>(ship_->GetShipPos().y + ship_->GetShipHeight()) - 9;
      seaEndY_ = 620;

      // Облака

      sky_ = new Sky(&cloudTex_, &seagullTex_, 150, 50, winWidth_, seaBeginY_);

      // Грунт
      seabed_ = new Ground(static_cast<float>(seaEndY_), static_cast<float>(winWidth_),
                           static_cast<float>(winHeight_));

      // Шрифт
      levelFont_ = LoadFontEx("Fonts/arial.ttf", fontSize_, NULL, 0);
      bldFont_ = LoadFontEx("Fonts/arialbd.ttf", 25, NULL, 0);

      // Создаём окна

      float winCentr = winWidth_ / 2;
      float winCntrHeight = winHeight_ / 2;
      float buttonWidth = 200.f;
      float buttonPadding = 25.f;

      const char *gameOvrTxt = {"GAME OVER"};
      const char *pauseTxt = {"PAUZE"};

      // Окно окончания игры
      gameOverWindow_ = new GameWindow(0.f, 0.f, winWidth_, winHeight_);
      gameOverWindow_->AddElement(std::make_unique<ElementButton>("TRY AGAIN", winCentr - (buttonWidth + buttonPadding), 450.f, buttonWidth, 50.f, &levelFont_, fontSize_ / 2, 0));
      gameOverWindow_->AddElement(std::make_unique<ElementButton>("EXIT", winCentr + buttonPadding, 450.f, buttonWidth, 50.f, &levelFont_, fontSize_ / 2, 1));
      float txtCntr = MeasureTextEx(levelFont_, gameOvrTxt, fontSize_ / 2, 0.f).x;
      gameOverWindow_->AddElement(std::make_unique<ElementText>(gameOvrTxt, winCentr - txtCntr, 350.f, &levelFont_, fontSize_, 2));
      // Картинка
      float posX = (gameOverWindow_->GetPosX() + gameOverWindow_->GetWidth() / 2) - GameOverTex_.width / 2;
      gameOverWindow_->AddElement(std::make_unique<ElementImage>(&GameOverTex_, posX, 140.f, 100.f, 50.f, 3));

      // Окно паузы
      pauseWindow_ = new GameWindow(0.f, 0.f, winWidth_, winHeight_);
      txtCntr = MeasureTextEx(levelFont_, pauseTxt, fontSize_ / 2, 0.f).x;
      pauseWindow_->AddElement(std::make_unique<ElementText>(pauseTxt, winCentr - txtCntr, winCntrHeight - fontSize_ / 2, &levelFont_, fontSize_, 2));

      // Создаём подлодки
      ResetLevel();
}

void SinkSub::Tick(float deltaTime)
{
      // Проверка статуса
      if (gameStatus_ == STATUS::RESETLEVEL)
      {
            level_ = 1;
            ResetLevel();
            gameStatus_ = STATUS::IDLE;
      }

      // Расчёт кадра
      runningTime_ += deltaTime;
      if (runningTime_ >= updateTime_)
      {
            frame_++;
            runningTime_ = 0.f;
            if (frame_ > maxFrame_)
                  frame_ = 0;
      }

      // Ввод
      if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_KP_4))
      {
            if (!isPause)
            {
                  ship_->DecreaseVelocity_X();
            }
      }

      if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_KP_6))
      {
            if (!isPause)
            {
                  ship_->IncreaseVelocity_X();
            }
      }

      if (IsKeyPressed(KEY_KP_1) && ship_->GetIsAlive() && bombCnt_ > 0)
      {
            DropBombs(POSITION::BACK);
      }

      if (IsKeyPressed(KEY_KP_3) && ship_->GetIsAlive() && bombCnt_ > 0)
      {
            DropBombs(POSITION::FRONT);
      }

      if (IsKeyPressed(KEY_SPACE))
      {
            ResetLevel();
      }
      if (IsKeyPressed(KEY_P))
      {
            isPause = !isPause;

            if (!isPause)
            {
                  pauseWindow_->ResetWindow();
            }
      }

      // Море
      DrawRectangle(0, seaBeginY_, winWidth_, winHeight_ - seaBeginY_, {220, 210, 160, 255});
      seabed_->Draw();

      sky_->Tick(frame_, isPause);

      // Глубинные бомбы
      if (bombList_.size() > 0)
      {

            for (Bomb &bomb : bombList_)
            {

                  bomb.Tick(frame_, isPause);

                  // Проверка столкновения с грунтом
                  if (CheckCollisionRecs(bomb.GetHitbox(), seabed_->GetHitBox()) && bomb.GetIsAlive())
                  {
                        bomb.Die();
                        bombCnt_++;
                  }

                  if (!bomb.GetIsAlive())
                  {
                        explList_.emplace_back(&explTex_, bomb.GetPosition().x + bomb.GetBombWidth() / 2,
                                               bomb.GetPosition().y + bomb.GetBombHeight(), 38.f, 38.f, 1.f);
                  }
            }

            // Удаление бомб
            bombList_.erase(std::remove_if(bombList_.begin(), bombList_.end(), [](Bomb &bomb)
                                           { return !(bomb.GetIsAlive()); }),
                            bombList_.end());
      }

      // Мины

      if (mineList_.size() > 0)
      {
            for (Mine &mine : mineList_)
            {
                  mine.Tick(isPause);

                  // Проверка столкновения с кораблём
                  if (CheckCollision(ship_, &mine) && ship_->GetIsAlive() && mine.GetIsAlive())
                  {
                        explList_.emplace_back(&splashTex_, mine.GetPosition().x,
                                               static_cast<float>(seaBeginY_) - 75.f / 2 + 15, 75.f, 75.f, 1.f);
                        mine.Die();
                        ship_->Die();
                        if (shipLifes_ > 0)
                        {
                              shipLifes_--;
                        }
                        else
                        {
                              isGameOver = true;
                        }
                  }

                  // Проверка всплытия мины
                  if ((mine.GetPosition().y <= seaBeginY_ - mine.GetMineHeight() / 2) && mine.GetIsAlive())
                  {
                        explList_.emplace_back(&splashTex_, mine.GetPosition().x,
                                               static_cast<float>(seaBeginY_) - 75.f / 2 + 15, 75.f, 75.f, 1.f);
                        mine.Die();
                  }
            }
            // Удаление мин
            mineList_.erase(std::remove_if(mineList_.begin(), mineList_.end(), [](Mine &mine)
                                           { return !(mine.GetIsAlive()); }),
                            mineList_.end());
      }

      // Корабль
      ship_->Tick(frame_, isPause);

      if (!subList_.empty())
      {
            for (Submarine &s : subList_)
            {
                  s.Ai(mineList_, isPause);
                  s.Tick(frame_, isPause);

                  // Проверка столкновения с бомбой
                  if (bombList_.size() > 0)
                  {
                        for (Bomb &bomb : bombList_)
                        {
                              if (s.CheckCollision(bomb.GetHitbox()))
                              {
                                    bomb.Die();
                                    s.Die();
                                    // ui_->AddScore();
                                    bombCnt_++;
                              }
                        }
                  }
            }

            // Удаление ПЛ
            subList_.erase(std::remove_if(subList_.begin(), subList_.end(), [](Submarine &sub)
                                          { return !(sub.GetIsAlive()); }),
                           subList_.end());
            // ui_->SetSubCnt(subList_.size());
      }

      // Проверяем подлодки и мины переходим на следующий уровень
      if (subList_.empty() && mineList_.empty() && explList_.empty())
      {
            level_++;
            ResetLevel();
      }

      if (explList_.size() > 0)
      {
            for (Explosion &expl : explList_)
            {
                  expl.Tick(frame_, isPause);
            }

            // Удаление взрывов
            explList_.erase(std::remove_if(explList_.begin(), explList_.end(), [](Explosion &expl)
                                           { return !(expl.GetIsAlive()); }),
                            explList_.end());
      }

      // проверяем не подбит ли корабль?

      if (!ship_->GetIsAlive() && !isGameOver)
      {
            ResetLevel();
      }

      DrawUI(frame_);
}

STATUS SinkSub::GetGameStatus()
{
      return gameStatus_;
}

SinkSub::~SinkSub()
{
      UnloadTexture(shipTex_);
      UnloadTexture(shipTexExpl_);
      UnloadTexture(bombTex_);
      UnloadTexture(explTex_);
      UnloadTexture(splashTex_);
      UnloadTexture(subTex_);
      UnloadTexture(subTexExpl_);
      UnloadTexture(mineTex_);
      UnloadTexture(cloudTex_);
      UnloadTexture(seagullTex_);
      UnloadTexture(iconTex_);
}

void SinkSub::SubInit()
{
      if (subList_.size() > 0)
      {
            subList_.clear();
      }

      // Установка значения в диапозоне
      level_ = std::clamp(level_, 0, 99);

      // Линейная интерполяция для диапазона от min до max
      int subCount = minSubs_ + (level_ * (maxSubs_ - minSubs_) / 99);

      // Создаём набор подлодок
      srand(time(NULL));
      float subWidth = 172.f;
      float subHeight = 38.f / 2;
      float rightLeft = 1.f;

      for (int i = 0; i < subCount; i++)
      {
            // Направление движения
            int dRightLeft = rand() % 6;
            if (dRightLeft % 2 == 0)
            {
                  rightLeft = -rightLeft;
            }

            // Позиция по x, за пределами экрана
            int dx = rand() % static_cast<int>(subWidth);
            float posX;

            if (rightLeft < 0)
            {
                  posX = winWidth_ + (dx + subWidth);
            }
            else
            {
                  posX = 0 - (dx + subWidth);
            }

            // Позиция по y
            int dy = rand() % static_cast<int>((seaEndY_ - seaBeginY_) / subHeight - 1);

            if (dy == 0)
            {
                  dy = 1;
            }
            float posY = seaBeginY_ + dy * subHeight;

            // Определяем скорость
            float minSpeed = 0.5f;
            float maxSpeed = 0.5f + (2.0f - 0.5f) * (level_ / 99.0f);
            std::random_device rd;                                    // Получаем случайное число из устройства
            std::mt19937 gen(rd());                                   // Инициализация генератора
            std::uniform_real_distribution<> dis(minSpeed, maxSpeed); // Определяем распределение
            float speed = dis(gen);

            // Добавляем подлодку
            subList_.push_back({&subTex_, &subTexExpl_, &mineTex_, ship_, seaBeginY_, posX, posY, 1.f, speed, rightLeft});

            // Назначаем рамки движения ПЛ
            subList_.back().SetBorders_X(0, winWidth_ - subWidth);
      }
}

void SinkSub::DropBombs(POSITION pos)
{
      if (!isPause)
      {
            if (pos == POSITION::BACK)
            {
                  bombList_.emplace_back(&bombTex_, ship_->GetShipPos().x,
                                         ship_->GetShipPos().y + ship_->GetShipHeight(), 1.f, bmbId);
            }
            else if (pos == POSITION::FRONT)
            {
                  bombList_.emplace_back(&bombTex_, ship_->GetShipPos().x + ship_->GetShipWidth() - 5,
                                         ship_->GetShipPos().y + ship_->GetShipHeight(), 1.f, bmbId);
            }
            bombCnt_--;
            bmbId++;
      }
}

void SinkSub::ResetLevel()
{
      // Расставляем ПЛ
      SubInit();
      // Определяем корабль
      ship_->SetAlive();
      ship_->SetToDefaultPos();
      // Чистим списки
      bombList_.clear();
      mineList_.clear();
      bombCnt_ = 4;
      bmbId = 0;
      // Регенерируем окружение
      sky_->ReInitClouds();
      seabed_->ReGenerteLandscape();
      // Определяем позицию сообщения
      SetLvlMsgPos();
      isLevelMsg = true;
      isFading = false;
      msgAlpha_ = 0;

      isGameOver = false;
      isPause = false;
}

void SinkSub::SetLvlMsgPos()
{
      int txtWidth = MeasureText(TextFormat("Level %i", level_), fontSize_);
      lvlMsgPos_ = {static_cast<float>(winWidth_ / 2 - txtWidth / 2),
                    static_cast<float>(winHeight_ / 2 - fontSize_ / 2)};
}

void SinkSub::DrawBacking(float posX, float posY, float width, float height)
{
      DrawRectangleRounded({posX, posY, width, height}, 0.20f, 0, {220, 210, 160, 255});
      DrawRectangleRoundedLines({posX, posY, width, height}, 0.25f, 0, 2.f, {121, 79, 57, 255});
}

void SinkSub::DrawBombIcon(float posX, float posY)
{
      DrawRectangle(posX, posY, 6.f, 10.f, {121, 79, 57, 255});
      DrawLine(posX - 1, posY + 3, posX + 7, posY + 3, {121, 79, 57, 255});
      DrawLine(posX - 1, posY + 7, posX + 7, posY + 7, {121, 79, 57, 255});
}

void SinkSub::SaveState()
{
      // Открываем файл для записи
      std::fstream fout("States/SinkSub.SB", std::ios::binary | std::ios::out);

      // Открыт ли файл для записи
      if (fout.is_open())
      {
            // Записываем уровень в файл
            fout.write((char *)&level_, sizeof(level_));

            fout.close();
      }
}

void SinkSub::LoadState()
{
      std::fstream fin("States/SinkSub.SB", std::ios::binary | std::ios::in);

      if (fin)
      {
            // Считываем уровень из файла
            fin.read((char *)&level_, sizeof(level_));
      }

      fin.close();
}

void SinkSub::DrawUI(int frame)
{
      // Рисуем подложку с жизнями и кол-вом подлодок
      DrawBacking(50.f, 42.f, 140.f, 65.f);
      DrawTextEx(bldFont_, TextFormat("X %i", shipLifes_), {135.f, 50.f}, 25, 0, {235, 235, 235, 255});
      DrawTextEx(bldFont_, TextFormat("X %i", subList_.size()), {135.f, 75.f}, 25, 0, {235, 235, 235, 255});

      // Рисуем подложку со счётом
      DrawBacking(1040.f, 42.f, 190.f, 65.f);
      DrawTextEx(bldFont_, TextFormat("Score %i", score_), {1055.f, 50.f}, 25, 0, {235, 235, 235, 255});

      float scrPosX = 1055.f;
      for (unsigned char i = 0; i < bombCnt_; i++)
      {
            DrawBombIcon(scrPosX, 85.f);
            scrPosX = scrPosX + 15;
      }

      Rectangle sourceText{0.f, 0.f, 49.f, 40.f};
      Rectangle destText{70.f, 52.f, 49.f, 40.f};
      DrawTexturePro(iconTex_, sourceText, destText, {0.0, 0.0}, 0.f, WHITE);

      // Вывод сообщения уровня
      if (isLevelMsg)
      {
            DrawTextEx(levelFont_, TextFormat("LEVEL %i", level_), lvlMsgPos_, fontSize_, 10, {128, 78, 56, msgAlpha_});

            if (frame % 1 == 0)
            {
                  if (msgAlpha_ < 255 && !isFading)
                  {
                        msgAlpha_ = msgAlpha_ + 5;
                        if (msgAlpha_ >= 255)
                        {
                              isFading = true;
                        }
                  }
                  else if (msgAlpha_ > 0 && isFading)
                  {
                        msgAlpha_ = msgAlpha_ - 5;
                        if (msgAlpha_ <= 0)
                        {
                              isFading = false;
                              msgAlpha_ = 0;
                              isLevelMsg = false;
                        }
                  }
            }
      }
      // Если пауза
      if (isPause)
      {
            pauseWindow_->Tick(GetMousePosition(), frame, gameStatus_);
      }

      // Если игра окончена
      if (isGameOver)
      {
            gameOverWindow_->Tick(GetMousePosition(), frame, gameStatus_);
            if (gameStatus_ == STATUS::RESETLEVEL)
            {
                  gameOverWindow_->ResetWindow();
            }
      }
}
