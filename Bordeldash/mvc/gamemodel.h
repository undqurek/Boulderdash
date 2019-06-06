#ifndef GAMEMODEL_H
#define GAMEMODEL_H

namespace mvc
{
	class GameView;
	class GamePart;

	class GameModel
	{
	private:
		GameView *__view;

		friend class GamePart;

	protected:
		GameView *__getView();

		virtual bool runBefore();
		virtual bool run();
		virtual bool runAfter();

	public:
		GameModel();
	};
}

#endif // GAMEMODEL_H
