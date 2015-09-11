#include "SpellCreators/IceBallSpellCreator.h"
#include "Screens/LevelScreen.h"

IceBallSpellCreator::IceBallSpellCreator(const SpellBean &spellBean, LevelMovableGameObject *owner) : SpellCreator(spellBean, owner)
{
}

void IceBallSpellCreator::executeSpell(const sf::Vector2f &target)
{
	SpellBean spellBean = m_spellBean;
	updateDamage(spellBean);
	int div = 0;
	int sign = 1;
	for (int i = 0; i < m_spellBean.count; i++)
	{
		IceBallSpell* newSpell = new IceBallSpell();
		spellBean.divergenceAngle = div * sign * m_spellBean.divergenceAngle;
		newSpell->load(spellBean, m_owner, target);
		m_screen->addObject(newSpell);
		sign = -sign;
		if (sign == -1)
		{
			div += 1;
		}
	}

	m_owner->setFightAnimationTime();
}