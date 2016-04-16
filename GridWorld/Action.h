#pragma once
class Action
{
	public:
		virtual int GetHashCode() const = 0;

		bool operator<(const Action& action) const {
			return GetHashCode() < action.GetHashCode();
	}
};
